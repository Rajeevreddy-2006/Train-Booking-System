#ifndef FARE_CALCULATOR_H
#define FARE_CALCULATOR_H

#include <string>
#include "domain/FareConfig.h"
#include "FareResult.h"

class FareCalculator {
public:
    static FareResult calculate( int trainNo,int distanceKm,const std::string& coachId,const FareConfig& config );
};

#endif
