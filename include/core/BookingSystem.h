#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H

#include "domain/Train.h"
#include "domain/User.h"
#include "domain/Ticket.h"
#include "domain/Station.h"
#include "infra/Storage.h"
#include "domain/FareConfig.h"
#include <vector>
#include <string>

class BookingSystem {
private:
    std::vector<Train> trains;
    std::vector<User> users;
    std::vector<Ticket> tickets;
    std::vector<Station> stations;
    FareConfig fareConfig;
    int nextTicketId;
public:
    BookingSystem();
    void loadAll();
    void saveAll();
    void rebuildSeatStateFromTickets();

    // train
    bool addTrain(int trainNo, const std::string& name);
    bool removeTrain(int trainNo);
    bool toggleTrainStatus(int trainNo);
    int getTrainCount() const;
    void displayAllTrains(const std::string& journeyDate);
    Train* getTrainByNumber(int trainNumber);
    std::vector<Train*> searchTrainsWithVacancy(int fromStationId,int toStationId);

    //coach
    bool addCoachToTrain(int trainNumber,const std::string& coachId,int seats);
    bool removeCoachFromTrain(int trainNumber,const std::string& coachId);
    bool updateCoachSeats(int trainNumber,const std::string& coachId,int newSeatCount);
    void displayTrainCoaches(int trainNumber,const std::string& journeyDate);

    //seats
    int getBookedSeatsCount(int trainNo,const std::string& coachId,const std::string& journeyDate);
    int getAvailableSeats(int trainNo,const std::string& coachId,const std::string& journeyDate);

    //Fare Config
    FareConfig& getFareConfig();
    void loadFareConfig();
    void saveFareConfig();

    //Routes
    bool assignRouteToTrain(int trainNumber,std::vector<RouteStop>& routestops);
    bool addStationToTrainRoute(int trainNumber,int stationId,int kmFromStart);
    bool removeStationFromTrainRoute(int trainNumber,int stationId);
    void displayTrainRoute(int trainNumber);
    void displayAllTrainsWithRoutes();
    void TrainRoute(int trainNumber);
    Station* getStationInTrainRoute(int trainNumber,int stationIndex);

    //user
    void addUser(User &user);
    User* getUserById(int userId);
    User* getUserByPhone(const std::string& phone);
    bool updateUserProfile(int userId,const std::string& newName,const std::string& newPhone);

    //station
    void addStation(const std::string& name);
    int getStationCount();
    void showAllStations();
    Station* getStationById(int id);
    int getStationIdByName(const std::string& name);
    bool renameStation(int stationId,const std::string& newName);
    bool removeStation(int stationId);

    //ticket
    std::string getStationNameById(int stationId);
    std::string bookTicket(int userId,int trainNumber,const std::string& coachId,int fromIndex,int toIndex,const std::string& journeyDate,
                               const std::string& passengerName,int passengerAge,const std::string& passengerGender);
    bool cancelTicket(int ticketId,const std::string& journeyDate);
    void showAllTickets();
    Ticket* findTicketById(int ticketId);
    std::vector<Ticket> getTicketByUser(int userId);
    std::vector<Ticket> getTicketByTrain(int trainNumber);
    Ticket* findTicketByPNR(const std::string& pnr);
    bool cancelTicketByPNR(const std::string& pnr);

    //file
    void loadFromFile(const std::string& filename);
    void saveToTicketFile(const std::string& filename);
    void saveToUserFile(const std::string& filename);
    
    //Reports
    void showSystemSummary();
    void showUserBookingReport(int userId);
    void showTrainDetailedReport(int trainNumber,const std::string& journeyDate);
};

#endif
//const -- “This function promises NOT to modify the object on which it is called.”,'this' pointer becomes const