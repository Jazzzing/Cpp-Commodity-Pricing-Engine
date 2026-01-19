#include <iostream>
#include <vector>
#include <memory>
#include "../include/EnergyFuture.h"

int main() {
    std::cout << "--- Commodity Pricing Engine Starting ---" << std::endl;

    std::vector<std::shared_ptr<Instrument>> portfolio;
    portfolio.push_back(std::make_shared<EnergyFuture>("Brent Crude Dec", 80.0, 0.05));

    for (const auto& instrument : portfolio) {
        std::cout << "Instrument: " << instrument->getName() 
                  << " | Price: $" << instrument->calculatePrice() << std::endl;
    }

    return 0;
}