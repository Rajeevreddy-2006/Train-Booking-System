#include "domain/Seat.h"
#include <iostream>

Seat::Seat(int number): seatNumber(number),booked(false) {}

bool Seat::isBooked() {
    return booked;
}

void Seat::book() {
    booked=true;
}

void Seat::cancel() {
    booked=false;
}

int Seat::getSeatNumber() {
    return seatNumber;
}