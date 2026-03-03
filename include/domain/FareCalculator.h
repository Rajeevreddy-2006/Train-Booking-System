#ifndef FARE_CALCULATOR_H
#define FARE_CALCULATOR_H

#include "FareContext.h"
#include "FareConfig.h"
#include "FareResult.h"

class FareCalculator {
public:
    static FareResult calculate(const FareContext& ctx,const FareConfig& config);
};

#endif