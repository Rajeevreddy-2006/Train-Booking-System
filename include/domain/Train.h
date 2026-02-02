#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <string>
#include "domain/Coach.h"

enum class TrainType {
    Passenger,
    Express,
    Premium
};

struct RouteStop {
    int stationId;
    int kmFromStart;
};

class Train {
private:
    int trainNumber;
    std::string trainName;
    TrainType type;
    bool active;
    std::vector<Coach> coaches;
    std::vector<RouteStop> routeStations;// ordered station IDs

public:
    Train(int trainNo, const std::string& name);

    //status
    bool isActive();
    void setActive(bool status);
    void activate();
    void deactivate();

    int getTrainNumber();
    std::string getTrainName();
    void displayTrain(const std::string& journeyDate);

    //Coach Management
    void addCoach(const std::string& coachId,int seats);
    bool removeCoach(const std::string& coachType);
    Coach* getCoachById(const std::string& coachId);
    std::vector<Coach>& getCoaches();

    //Seat Booking
    bool bookSeat(const std::string& coachId, int seatNumber);
    bool cancelSeat(const std::string& coachId, int seatNumber);
    int  bookSeatAuto(const std::string& coachId);

    //traintype
    TrainType getType();

    //Route Management
    void addRouteStop(int stationId, int kmFromStart);
    void removeStationFromRoute(int stationId);
    std::vector<RouteStop>& getRoute();
    void clearRoute();

    bool coversRoute(int fromStationId, int toStationId);
};

#endif
