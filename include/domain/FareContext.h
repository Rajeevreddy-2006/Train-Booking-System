#ifndef FARE_CONTEXT_H
#define FARE_CONTEXT_H

#include <string>

struct FareContext {
    int trainNo = 0;
    int distanceKm = 0;
    std::string coachId;

    bool isSuperfast = false;
    bool isTatkal = false;
};

#endif