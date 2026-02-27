#pragma once
#include <vector>

// The data container for the variables passed from Python
struct GSParameters {
    double S0;       
    double sigma1;   
    double delta0;   
    double sigma2;   
    double kappa;    
    double alpha;    
    double rho;
    double r;
};

class MonteCarloEngine {
public:
    // Constructor
    MonteCarloEngine(const GSParameters& params, int numPaths, int numSteps, double T);

    // The main simulation function
    std::vector<double> runSimulation();

private:
    GSParameters m_params;
    int m_numPaths;
    int m_numSteps;
    double m_T;
    double m_dt;
    
    // We only return the terminal prices to save memory transfer overhead,
    // but we use a cache-friendly 1D vector internally if we need full paths.
    std::vector<double> m_terminalPrices; 
};