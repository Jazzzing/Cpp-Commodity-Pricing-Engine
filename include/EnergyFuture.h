#pragma once
#include "Instrument.h"

class EnergyFuture : public Instrument {
private:
    std::string m_name;
    double m_spotPrice;
    double m_costOfCarry;

public:
    EnergyFuture(std::string name, double spot, double carry)
        : m_name(name), m_spotPrice(spot), m_costOfCarry(carry) {}

    double calculatePrice() const override {
        return m_spotPrice * (1 + m_costOfCarry);
    }

    std::string getName() const override {
        return m_name;
    }
};