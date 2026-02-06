#ifndef TICKET_H
#define TICKET_H

#include <string>
#include "FareResult.h"

class Ticket {
private:
    int ticketId;
    std::string pnr;

    int trainNumber;
    std::string trainName;

    std::string fromStation;
    std::string toStation;
    std::string journeyDate;

    std::string coachId;
    int seatNumber;
    bool isWaiting;

    int userId;
    std::string passengerName;
    int passengerAge;
    std::string passengerGender;

    FareResult fareResult;
public:
    Ticket(int ticketId,const std::string& pnr,int trainNumber,const std::string& trainName,const std::string& coachId,
        int seatNumber,int userId,const std::string& journeyDate,const std::string& fromStation,const std::string& toStation,
        const std::string& passengerName,int passengerAge,const std::string& passengerGender,const FareResult& fareResult,
        bool isWaiting
    );

    /* ---------- Getters ---------- */
    int getTicketId();
    std::string getPnr();

    int getTrainNumber();
    std::string getTrainName();

    std::string getFromStation();
    std::string getToStation();
    std::string getjourneyDate();

    std::string getCoachId();
    int getSeatNumber();
    bool getIsWaiting();

    int getUserId();

    std::string getPassengerName();
    int getPassengerAge();
    std::string getPassengerGender();

    double getTotalFare();
    FareResult& getFareResult();

    void displayTicket();
    void generateHTML(const std::string& filename,const std::string& userName);
};

#endif

