#include "domain/FareCalculator.h"
#include <stdexcept>

FareResult FareCalculator::calculate(const FareContext& ctx,const FareConfig& config){
    FareResult result;
    auto it = config.coachRatePerKm.find(ctx.coachId);
    if (it == config.coachRatePerKm.end()) {
        throw std::runtime_error("Invalid coachId in FareCalculator");
    }
    result.baseFare = ctx.distanceKm * it->second;
    if (ctx.isSuperfast) {
        result.superfastCharge = config.superfastCharge;
    }
    result.reservationCharge = config.reservationCharge;
    if (ctx.isTatkal) {
        result.tatkalCharge = config.tatkalCharge;
    }
    double subtotal = result.baseFare + result.superfastCharge + result.reservationCharge + result.tatkalCharge;

    result.gst = subtotal * (config.gstPercent / 100.0);
    double totalWithTax = subtotal + result.gst;

    result.discount = totalWithTax * (config.discountPercent / 100.0);
    result.totalFare = totalWithTax - result.discount;

    return result;
}