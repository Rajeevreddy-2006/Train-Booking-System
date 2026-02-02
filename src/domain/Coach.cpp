#include "domain/Coach.h"
#include <iostream>
#include <iomanip>

Coach::Coach(const std::string& id, int seatsCount)
    : coachId(id), totalSeats(seatsCount)
{
    for (int i = 1; i <= totalSeats; ++i) {
        seats.emplace_back(i);
    }
}

void Coach::displayCoach(const std::string& journeyDate) {
    int booked = 0;
    auto it = bookedSeatsByDate.find(journeyDate);
    if (it != bookedSeatsByDate.end()) {
        booked = it->second.size();
    }
    int available = totalSeats - booked;
    std::cout << std::left
              << std::setw(5) << coachId
              << " | Total: "
              << std::setw(4) << totalSeats
              << " | Available: "
              << std::setw(4) << available
              << "\n";
}

std::string& Coach::getCoachId() { return coachId; }

int Coach::getTotalSeats() { return totalSeats; }

int Coach::getAvailableSeats(const std::string& journeyDate) {
    auto it = bookedSeatsByDate.find(journeyDate);
    int booked = (it == bookedSeatsByDate.end()) ? 0 : it->second.size();
    return totalSeats - booked;
}

int Coach::getWaitingCount(const std::string& journeyDate) {
    auto it = waitingListByDate.find(journeyDate);
    return (it == waitingListByDate.end()) ? 0 : it->second.size();
}

// Seat operations
int Coach::assignSeat(const std::string& journeyDate) {
    auto& booked = bookedSeatsByDate[journeyDate];
    for (int seat = 1; seat <= totalSeats; ++seat) {
        if (booked.find(seat) == booked.end()) {
            booked.insert(seat);
            return seat;
        }
    }
    return -1; // full
}

void Coach::releaseSeat(const std::string& journeyDate, int seatNumber) {
    auto& booked = bookedSeatsByDate[journeyDate];
    booked.erase(seatNumber);
}

void Coach::updateSeatCount(int newTotalSeats) {
    seats.clear();
    totalSeats = newTotalSeats;
    bookedSeatsByDate.clear();
    waitingListByDate.clear();
    for (int i = 1; i <= totalSeats; ++i) {
        seats.emplace_back(i);
    }
}

// int Coach::assignSeat() {
//     if (availableSeats == 0) return -1;

//     for (auto& seat : seats) {
//         if (!seat.isBooked()) {
//             seat.book();
//             availableSeats--;
//             return seat.getSeatNumber();
//         }
//     }
//     return -1;
// }

bool Coach::bookSeat(int seatNumber) {
    if (seatNumber < 1 || seatNumber > totalSeats) return false;

    if (!seats[seatNumber - 1].isBooked()) {
        seats[seatNumber - 1].book();
        return true;
    }
    return false;
}

// bool Coach::cancelSeat(int seatNumber) {
//     if (seatNumber < 1 || seatNumber > totalSeats)
//         return false;

//     if (seats[seatNumber - 1].isBooked()) {
//         seats[seatNumber - 1].cancel();
//         availableSeats++;
//         return true;
//     }
//     return false;
// }

void Coach::markSeatBooked(const std::string& journeyDate, int seatNumber) {
    bookedSeatsByDate[journeyDate].insert(seatNumber);
}

int Coach::getAvailableSeats(const std::string& journeyDate) const {
    int booked = 0;
    auto it = bookedSeatsByDate.find(journeyDate);
    if (it != bookedSeatsByDate.end()) {
        booked = it->second.size();
    }
    return totalSeats - booked;
}

// Waiting list
void Coach::addToWaitingList(const std::string& journeyDate,const WLDataType& entry) {
    waitingListByDate[journeyDate].push(entry);
}

bool Coach::hasWaiting(const std::string& journeyDate) {
    auto it = waitingListByDate.find(journeyDate);
    return it != waitingListByDate.end() && !it->second.empty();
}

WLDataType Coach::popFromWaitingList(const std::string& journeyDate) {
    if (!hasWaiting(journeyDate))
        return {-1, "", 0, "", 0.0};

    WLDataType entry = waitingListByDate[journeyDate].front();
    waitingListByDate[journeyDate].pop();
    return entry;
}