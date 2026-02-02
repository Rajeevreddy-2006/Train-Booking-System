#ifndef PASSENGER_AUTH_H
#define PASSENGER_AUTH_H

#include <core/BookingSystem.h>
#include <string>

class PassengerAuth {
public:
    static int login(BookingSystem& system); // returns userId if login successful, -1 otherwise

    static int registerUser(BookingSystem& system); // creates new account and returns userId

    static bool changePassword(BookingSystem& system,int userId);
};

#endif
