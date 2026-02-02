#include "domain/FareCalculator.h"
#include <stdexcept>

FareResult FareCalculator::calculate(int trainNo,int distanceKm,const std::string& coachId,const FareConfig& config) {
    FareResult result{};

    auto coachIt = config.coachRatePerKm.find(coachId);
    if (coachIt == config.coachRatePerKm.end())
        throw std::runtime_error("Invalid coach type");

    double baseFare = coachIt->second * distanceKm;

    double trainCharge = 0.0;
    auto trainIt = config.trainCharge.find(trainNo);
    if (trainIt != config.trainCharge.end())
        trainCharge = trainIt->second;

    double subtotal = baseFare + trainCharge;

    double gst = subtotal * (config.gstPercent / 100.0);
    double discount = subtotal * (config.discountPercent / 100.0);

    result.baseFare       = baseFare;
    result.trainCharge    = trainCharge;
    result.gstAmount      = gst;
    result.discountAmount = discount;
    result.totalFare      = subtotal + gst - discount;

    return result;
}
