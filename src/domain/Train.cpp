#include "domain/Train.h"
#include <iostream>
#include <algorithm>

Train::Train(int trainno,const std::string& name)
    : trainNumber(trainno), trainName(name) ,active(true) {}

//status
bool Train::isActive() { return active; }
void Train::setActive(bool status) { active = status; }

void Train::activate() { active = true; }
void Train::deactivate() { active = false; }

int Train::getTrainNumber() { return trainNumber; }
std::string Train::getTrainName() { return trainName; }

void Train::displayTrain(const std::string& journeyDate) {
    std::cout << "\n=====================================\n";
    std::cout << "Date     : " << journeyDate << "\n";
    std::cout << "Train No : " << trainNumber << "\n";
    std::cout << "Name     : " << trainName << "\n";
    std::cout << "Status   : " << (active ? "ACTIVE" : "INACTIVE") << "\n";
    std::cout << "Coaches  : ";
    if (coaches.empty()) {
        std::cout << "None\n";
    } else {
        std::cout << "\n";
        for (auto& coach : coaches) {
            coach.displayCoach(journeyDate);
        }
    }
    std::cout << "Route    : ";
    if (routeStations.empty()) {
        std::cout << "Not assigned\n";
    } else {
        for (int i = 0; i < routeStations.size(); ++i) {
            std::cout << routeStations[i].stationId;
            if (i + 1 < routeStations.size())
                std::cout << " -> ";
        }
        std::cout << "\n";
    }
    std::cout << "=====================================\n";
}

//coaches
void Train::addCoach(const std::string& coachId,int seats) {
    for (auto& c : coaches) { //prevent duplicates
        if (c.getCoachId() == coachId) {
            std::cout << "Coach already exists in train.\n";
            return;
        }
    }
    coaches.emplace_back(coachId,seats);
}

bool Train::removeCoach(const std::string& coachId) {
    for (auto it = coaches.begin(); it != coaches.end(); ++it) {
        if (it->getCoachId() == coachId) {
            coaches.erase(it);
            return true;
        }
    }
    return false;
}

Coach* Train::getCoachById(const std::string& coachId) {
    for (auto& coach : coaches) {
        if (coach.getCoachId() == coachId) {
            return &coach;
        }
    }
    return nullptr;
}

std::vector<Coach>& Train::getCoaches() { return coaches; }

//booking
bool Train::bookSeat(const std::string& coachid,int seatNumber) {
    for(auto &c:coaches){
        if(c.getCoachId() == coachid){
            return c.bookSeat(seatNumber);
        }
    }
    return false;
}

// bool Train::cancelSeat(const std::string& coachid,int seatNumber) {
//     for(auto &c:coaches){
//         if(c.getCoachId() == coachid){
//             return c.cancelSeat(seatNumber);
//         }
//     }
//     return false;
// }

// int Train::bookSeatAuto(const std::string& coachid) {
//     for(auto& coach:coaches){
//         if(coach.getCoachId() == coachid) {
//             return coach.assignSeat();
//         }
//     }
//     return -1;
// }

//traintype
TrainType Train::getType() {
    return type;
}

//Routes
void Train::addRouteStop(int stationId, int kmFromStart) {
    routeStations.push_back({stationId, kmFromStart});
}

void Train::removeStationFromRoute(int stationId) {
    auto it = std::find_if(routeStations.begin(),routeStations.end(),
        [&](const RouteStop& stop) {
            return stop.stationId == stationId;
        }
    );
    if (it != routeStations.end())
        routeStations.erase(it);
}

std::vector<RouteStop>& Train::getRoute() { return routeStations; }

void Train::clearRoute() { routeStations.clear(); }

bool Train::coversRoute(int fromStationId, int toStationId) {
    int fromIndex = -1;
    int toIndex = -1;
    for (int i = 0; i < routeStations.size(); ++i) {
        if (routeStations[i].stationId == fromStationId && fromIndex == -1)
            fromIndex = i;
        if (routeStations[i].stationId == toStationId)
            toIndex = i;
    }
    return (fromIndex != -1 && toIndex != -1 && fromIndex < toIndex);
}
