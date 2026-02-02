#pragma once
#include "../core/BookingSystem.h"

class PassengerConsole {
private:
    BookingSystem& bookingSystem;
    int userId;   // logged-in passenger

public:
    PassengerConsole(BookingSystem& system, int userId);

    void start(BookingSystem& system);   // passenger menu loop

private:
    void searchTrainsFlow();
    void bookTicketFlow();
    void cancelTicketFlow();
    void showMyTicketsFlow();
    void profileFlow(BookingSystem& system);
};
