// #ifndef TICKET_H
// #define TICKET_H

// #include <string>
// #include "FareCalculator.h"

// class Ticket {
// private:
//     int ticketId;
//     std::string pnr;
//     int trainNumber;
//     std::string coachId;
//     int seatNumber;
//     int userId;
//     std::string journeyDate;
//     std::string passengerName;
//     int passengerAge;
//     std::string passengerGender;
//     FareResult fareResult;
// public:
//     Ticket(int ticketId,const std::string& pnr,int trainNumber,const std::string& coachId,int seatNumber,int userId,
//            const std::string& journeyDate,const std::string& passengerName,int passengerAge,const std::string& passengerGender,
//            const FareResult& fareResult);
//     //Getters
//     int getTicketId();
//     std::string getPnr();
//     int getTrainNumber();
//     std::string getCoachId();
//     int getSeatNumber();
//     int getUserId();
//     std::string getjourneyDate();
//     double getTotalFare() const;
//     const FareResult& getFareResult() const;
//     std::string getPassengerName();
//     int getPassengerAge();
//     std::string getPassengerGender();

//     void displayTicket();
//     void generateHTML(const std::string& filename,const std::string& userName);
// };

// #endif
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
    int getTicketId() const;
    std::string getPnr() const;

    int getTrainNumber() const;
    std::string getTrainName() const;

    std::string getFromStation() const;
    std::string getToStation() const;
    std::string getjourneyDate() const;

    std::string getCoachId() const;
    int getSeatNumber() const;
    bool getIsWaiting() const;

    int getUserId() const;

    std::string getPassengerName() const;
    int getPassengerAge() const;
    std::string getPassengerGender() const;

    double getTotalFare() const;
    const FareResult& getFareResult() const;

    void displayTicket() const;
    void generateHTML(const std::string& filename,const std::string& userName);
};

#endif

