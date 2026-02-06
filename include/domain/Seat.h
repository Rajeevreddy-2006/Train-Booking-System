#ifndef SEAT_H
#define SEAT_H

class Seat {
private:
    int seatNumber;
    bool booked;

public:
    Seat(int number);

    bool isBooked();
    void book();
    void cancel();
    int getSeatNumber();
};

#endif
