#pragma once
#include <string>

class Instrument {
public:
    virtual ~Instrument() = default;
    virtual double calculatePrice() const = 0;
    virtual std::string getName() const = 0;
};