//#ifndef #define #endif ensure that a header file is included only once, preventing redefinition errors during compilation.
#ifndef COACH_H //it is basically if not defined pls define it.
#define COACH_H

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "domain/Seat.h"
#include "domain/fareResult.h"

struct WaitingListEntry {
    int userId;
    std::string passengerName;
    int passengerAge;
    std::string passengerGender;
    FareResult fare;
};

using WLDataType = WaitingListEntry;

class Coach {
private:
    std::string coachId;     // GEN(General), SL(Non-AC), AC3(AC 3 Tier), AC2, AC1, CC(Chair Car)
    int totalSeats;
    std::vector<Seat> seats; //Right now it is not useful,but it is useful if we want to make seat more specific.(upper/lower/window seat)
    std::unordered_map<std::string, std::unordered_set<int>> bookedSeatsByDate; //date,occupied seats
    std::unordered_map<std::string, std::queue<WLDataType>> waitingListByDate; //date,wl
public:
    Coach(const std::string& id, int seatsCount);

    // Display
    void displayCoach(const std::string& journeyDate);

    // Getters
    std::string& getCoachId();
    int getTotalSeats();
    int getWaitingCount(const std::string& journeyDate);

    // Seat operations
    void updateSeatCount(int newTotalSeats);
    bool bookSeat(int seatNumber);
    int assignSeat(const std::string& journeyDate);
    void releaseSeat(const std::string& journeyDate, int seat);
    void markSeatBooked(const std::string& journeyDate, int seatNumber);
    int getAvailableSeats(const std::string& journeyDate);

    // Waiting list
    void addToWaitingList(const std::string& journeyDate,const WLDataType& entry);
    bool hasWaiting(const std::string& journeyDate);
    WLDataType popFromWaitingList(const std::string& journeyDate);
};

#endif
