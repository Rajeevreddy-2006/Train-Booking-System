#ifndef FARE_RESULT_H
#define FARE_RESULT_H

struct FareResult {
    double baseFare = 0.0;
    double superfastCharge = 0.0;
    double reservationCharge = 0.0;
    double tatkalCharge = 0.0;

    double gst = 0.0;
    double discount = 0.0;

    double totalFare = 0.0;
};

#endif