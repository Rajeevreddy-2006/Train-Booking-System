#ifndef FARE_CONFIG_H
#define FARE_CONFIG_H

#include <map>
#include <string>

struct FareConfig {
    std::map<std::string, double> coachRatePerKm;

    double superfastCharge = 0.0;
    double reservationCharge = 0.0;
    double tatkalCharge = 0.0;

    double gstPercent = 0.0;
    double discountPercent = 0.0;
};

#endif