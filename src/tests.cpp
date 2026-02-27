#include "MonteCarloEngine.h"
#include <iostream>
#include <cassert>
#include <cmath>

void test_extreme_volatility() {
    // 500% Volatility!
    GSParameters params;
    params.S0 = 60.0;
    params.sigma1 = 5.0;   // 500% Spot Volatility
    params.delta0 = 0.05;
    params.sigma2 = 0.80;   // High Yield Volatility
    params.kappa = 1.5;
    params.alpha = 0.10;
    params.rho = 0.4;
    params.r = 0.03; // Risk-free rate
    MonteCarloEngine engine(params, 1000, 100, 1.0);
    auto results = engine.runSimulation();

    for (double p : results) {
        assert(p > 0 && "Price should never be negative even in high vol!");
        assert(!std::isnan(p) && "Price should not be NaN!");
    }
    std::cout << "✅ Extreme Volatility Test Passed!" << std::endl;
}

void test_zero_volatility() {
    // No randomness
    GSParameters params;
    params.S0 = 60.0;
    params.sigma1 = 0.0;
    params.delta0 = 0.03;
    params.sigma2 = 0.0;
    params.kappa = 0.8;
    params.alpha = 0.05;
    params.rho = 0.5;
    params.r = 0.02; // Risk-free rate
    MonteCarloEngine engine(params, 10, 100, 1.0);
    auto results = engine.runSimulation();

    // With zero vol, every path should be identical (deterministic)
    for (size_t i = 1; i < results.size(); ++i) {
        assert(std::abs(results[i] - results[0]) < 1.0);
    }
    std::cout << "✅ Zero Volatility (Deterministic) Test Passed!" << std::endl;
}

int main() {
    std::cout << "Starting Unit Tests..." << std::endl;
    test_extreme_volatility();
    test_zero_volatility();
    std::cout << "All Tests Passed!" << std::endl;
    return 0;
}