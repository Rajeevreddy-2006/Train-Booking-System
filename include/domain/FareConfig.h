#ifndef FARE_CONFIG_H
#define FARE_CONFIG_H

#include <unordered_map>
#include <string>

class FareConfig {
public:
    std::unordered_map<std::string, double> coachRatePerKm;
    std::unordered_map<int, double> trainCharge; 
    double gstPercent = 0.0;
    double discountPercent = 0.0;
};

#endif
