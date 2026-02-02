#pragma once

#include "../core/BookingSystem.h"

class PassengerPortal {
private:
    BookingSystem& bookingSystem;

public:
    explicit PassengerPortal(BookingSystem& system);
    void start();   // auth gate + passenger session
};
