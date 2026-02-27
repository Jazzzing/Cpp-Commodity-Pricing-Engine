#include <iostream>
#include "MonteCarloEngine.h"

int main() {
    // 1. Manually set the parameters we got from Python
    GSParameters params;
    params.S0 = 65.63;
    params.sigma1 = 0.36;
    params.delta0 = -0.05; // Using a realistic value
    params.sigma2 = 0.50;
    params.kappa = 1.5;
    params.alpha = 0.10;
    params.rho = 0.4;

    // 2. Initialize engine: 10,000 paths, 252 steps, 1.0 year
    MonteCarloEngine engine(params, 10000, 252, 1.0);

    // 3. Run and get results
    std::vector<double> results = engine.runSimulation();

    // 4. Print a few results to verify
    std::cout << "First 5 simulated terminal prices:" << std::endl;
    for(int i = 0; i < 5; ++i) {
        std::cout << results[i] << std::endl;
    }

    return 0;
}