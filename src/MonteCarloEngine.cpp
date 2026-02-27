#include "MonteCarloEngine.h"
#include <cmath>
#include <random>

MonteCarloEngine::MonteCarloEngine(const GSParameters& params, int numPaths, int numSteps, double T)
    : m_params(params), m_numPaths(numPaths), m_numSteps(numSteps), m_T(T) {
    m_dt = m_T / m_numSteps;
    m_terminalPrices.resize(m_numPaths, 0.0);
}

std::vector<double> MonteCarloEngine::runSimulation() {
    double sqrt_dt = std::sqrt(m_dt);
    double sqrt_one_minus_rho_sq = std::sqrt(1.0 - m_params.rho * m_params.rho);

    // Standard Random Setup
    std::mt19937 generator(42); 
    std::normal_distribution<double> standard_normal(0.0, 1.0);

    // loop with parallelization using OpenMP
    for (int i = 0; i < m_numPaths; ++i) {
        double current_log_S = std::log(m_params.S0);
        double current_delta = m_params.delta0;

        for (int j = 0; j < m_numSteps; ++j) {

            double Z1 = standard_normal(generator);
            double Zx = standard_normal(generator);
            double Z2 = m_params.rho * Z1 + sqrt_one_minus_rho_sq * Zx;

            // Update Yield and Spot
            double next_delta = current_delta + m_params.kappa * (m_params.alpha - current_delta) * m_dt 
                                + m_params.sigma2 * sqrt_dt * Z2;
            
            double drift = m_params.r - current_delta - (0.5 * m_params.sigma1 * m_params.sigma1);
            double next_log_S = current_log_S + drift * m_dt + m_params.sigma1 * sqrt_dt * Z1;

            current_delta = next_delta;
            current_log_S = next_log_S;
        }
        m_terminalPrices[i] = std::exp(current_log_S);
    }

    return m_terminalPrices;
}