#include "core/BookingSystem.h"
#include "infra/Storage.h"

#include <iostream>
#include <fstream>
#include <cstdio> // for std::remove
#include <iomanip>
#include <cctype>

#include <ui/ConsoleStyle.h>
#include "domain/FareCalculator.h"
#include <algorithm>
#include <string>
#include <ctime>

std::string compactDate(const std::string& date) {
    std::string res = date;
    res.erase(std::remove(res.begin(), res.end(), '-'), res.end());
    return res; // YYYYMMDD
}

std::string currentTimeHHMMSS() {
    std::time_t t = std::time(nullptr);
    std::tm* local = std::localtime(&t);
    char buf[7];
    std::strftime(buf, sizeof(buf), "%H%M%S", local);
    return buf; // HHMMSS
}

static std::string generatePNR(int trainNumber,const std::string& journeyDate) {
    return "T" +std::to_string(trainNumber) + compactDate(journeyDate) + currentTimeHHMMSS();
}

BookingSystem::BookingSystem()
    : nextTicketId(1) {}

void BookingSystem::loadAll() {
    stations = Storage::loadStations("data/stations.txt");
    trains   = Storage::loadTrains("data/trains.txt");
    tickets  = Storage::loadTickets("data/tickets.txt");
    users    = Storage::loadUsers("data/users.txt");
    rebuildSeatStateFromTickets();
    loadFareConfig();
}

void BookingSystem::saveAll() {
    Storage::saveStations(stations, "data/stations.txt");
    Storage::saveTrains(trains, "data/trains.txt");
    Storage::saveTickets(tickets, "data/tickets.txt");
    Storage::saveUsers(users, "data/users.txt");
}

void BookingSystem::rebuildSeatStateFromTickets() {
    for (auto& ticket : tickets) {
        Train* train = getTrainByNumber(ticket.getTrainNumber());
        if (!train) continue;
        Coach* coach = train->getCoachById(ticket.getCoachId());
        if (!coach) continue;
        coach->markSeatBooked(
            ticket.getjourneyDate(),
            ticket.getSeatNumber()
        );
    }
}

//train
bool BookingSystem::addTrain(int trainNo,const std::string& name) {
    for (auto& t : trains)
        if (t.getTrainNumber() == trainNo)
            return false;
    trains.emplace_back(trainNo, name);
    return true;
}

bool BookingSystem::removeTrain(int trainNo) {
    for (auto it = trains.begin(); it != trains.end(); ++it) {
        if (it->getTrainNumber() == trainNo) {
            trains.erase(it);
            return true;
        }
    }
    return false;
}

bool BookingSystem::toggleTrainStatus(int trainNo) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNo) {
            train.isActive() ? train.deactivate() : train.activate();
            return true;
        }
    }
    return false;
}

int BookingSystem::getTrainCount() const {
    return trains.size();
}

void BookingSystem::displayAllTrains(const std::string& journeyDate) {
    if (trains.empty()) {
        std::cout << "No trains available.\n";
        return;
    }
    for (auto& train : trains) {
        train.displayTrain(journeyDate);
    }
}

Train* BookingSystem::getTrainByNumber(int trainNumber) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNumber) {
            return &train; 
        }
    }
    return nullptr;
}

std::vector<Train*> BookingSystem::searchTrainsWithVacancy(int fromStationId,int toStationId) {
    std::vector<Train*> result;

    for (auto& train : trains) {
        if (train.coversRoute(fromStationId, toStationId)) {
            result.push_back(&train);
        }
    }
    return result;
}

//coach
bool BookingSystem::addCoachToTrain(int trainNumber,const std::string& coachId,int seats) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNumber) {
            for (auto& coach : train.getCoaches()) {
                if (coach.getCoachId() == coachId) {
                    std::cout << "Coach already exists.\n";
                    return false;
                }
            }
            train.addCoach(coachId, seats);
            return true;
        }
    }
    return false;
}

bool BookingSystem::removeCoachFromTrain(int trainNumber,const std::string& coachId) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNumber) {
            return train.removeCoach(coachId);
        }
    }
    return false;
}

bool BookingSystem::updateCoachSeats(int trainNumber,const std::string& coachId,int newSeatCount) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNumber) {
            for (auto& coach : train.getCoaches()) {
                if (coach.getCoachId() == coachId) {
                    coach.updateSeatCount(newSeatCount);
                    return true;
                }
            }
        }
    }
    return false;
}

void BookingSystem::displayTrainCoaches(int trainNumber,const std::string& journeyDate) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNumber) {
            std::cout << "\nTrain " << train.getTrainNumber()
                      << " - " << train.getTrainName() << "\n";
            std::cout << "--------------------------------\n";
            if (train.getCoaches().empty()) {
                std::cout << "No coaches added.\n";
                return;
            }
            for (auto& coach : train.getCoaches()) {
                coach.displayCoach(journeyDate);
            }
            return;
        }
    }
    std::cout << "Train not found.\n";
}

//seats
int BookingSystem::getBookedSeatsCount(int trainNo,const std::string& coachId,const std::string& journeyDate) {
    int booked = 0;
    for (auto& t : tickets) {
        if (t.getTrainNumber() == trainNo && t.getCoachId() == coachId && t.getjourneyDate() == journeyDate) {
            booked++;
        }
    }
    return booked;
}

int BookingSystem::getAvailableSeats(int trainNo,const std::string& coachId,const std::string& journeyDate) {
    Train* train = getTrainByNumber(trainNo);
    if (!train) return -1;
    int totalSeats = -1;
    for (auto& c : train->getCoaches()) {
        if (c.getCoachId() == coachId) {
            totalSeats = c.getTotalSeats();
            break;
        }
    }
    if (totalSeats == -1) return -1;
    int booked = getBookedSeatsCount(trainNo, coachId, journeyDate);
    return totalSeats - booked;
}

//fare
FareConfig& BookingSystem::getFareConfig() { return fareConfig; }

void BookingSystem::loadFareConfig() {
    if (!Storage::loadFareConfig(fareConfig, "data/fare_config.txt")) {
        throw std::runtime_error(
            "Fare configuration file missing or unreadable."
        );
    }
}

void BookingSystem::saveFareConfig() {
    if (!Storage::saveFareConfig(fareConfig, "data/fare_config.txt")) {
        throw std::runtime_error(
            "Failed to save fare configuration."
        );
    }
}

//Route
bool BookingSystem::assignRouteToTrain(int trainNumber,std::vector<RouteStop>& routeStops) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNumber) {
            train.clearRoute();
            for (auto& stop : routeStops) {
                train.addRouteStop(stop.stationId, stop.kmFromStart);
            }
            return true;
        }
    }
    return false;
}

bool BookingSystem::addStationToTrainRoute(int trainNumber,int stationId,int kmFromStart) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNumber) {
            train.addRouteStop(stationId, kmFromStart);
            return true;
        }
    }
    return false;
}

bool BookingSystem::removeStationFromTrainRoute(int trainNumber,int stationId) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNumber) {
            train.removeStationFromRoute(stationId);
            return true;
        }
    }
    return false;
}

void BookingSystem::displayTrainRoute(int trainNumber) {
    for (auto& train : trains) {
        if (train.getTrainNumber() == trainNumber) {
            std::cout << "\nRoute for Train "
                      << train.getTrainNumber()
                      << " - " << train.getTrainName() << "\n";

            if (train.getRoute().empty()) {
                std::cout << "No route assigned.\n";
                return;
            }
            for (auto [id,dist] : train.getRoute()) {
                Station* s = getStationById(id);
                if (s)
                    std::cout << s->getName() << " -> ";
            }
            std::cout << "END\n";
            return;
        }
    }
    std::cout << "Train not found.\n";
}

void BookingSystem::displayAllTrainsWithRoutes() {
    if (trains.empty()) {
        std::cout << "No trains available.\n";
        return;
    }
    std::cout << std::left
              << std::setw(10) << "Train No"
              << std::setw(23) << "Train Name"
              << "Route\n";
    std::cout << "-------------------------------------------------------------\n";
    for (auto& train : trains) {
        std::cout << std::left
                  << std::setw(10) << train.getTrainNumber()
                  << std::setw(23) << train.getTrainName();
        auto& route = train.getRoute();
        for (int i = 0; i < route.size(); ++i) {
            Station* st = getStationById(route[i].stationId);
            if (st) {
                std::cout << st->getName();
                if (i != route.size() - 1)
                    std::cout << " -> ";
            }
        }
        std::cout << "\n";
    }
}

void BookingSystem::TrainRoute(int trainNumber) {
    for (auto& train : trains) {
        if (train.getTrainNumber() != trainNumber) continue;

        int idx = 1;
        for (auto& stop : train.getRoute()) {
        Station* s = getStationById(stop.stationId);
        std::cout << idx++ << ". " << s->getName()
              << " (" << stop.kmFromStart << " km)\n";
        }
    }
}

Station* BookingSystem::getStationInTrainRoute(int trainNumber,int stationIndex) {
    for (auto& train : trains) {
        if (train.getTrainNumber() != trainNumber) continue;

        if (stationIndex < 1 ||
            stationIndex > train.getRoute().size())
            return nullptr;

        int stationId=train.getRoute()[stationIndex - 1].stationId;
        return getStationById(stationId);
    }
    return nullptr;
}

//user
void BookingSystem::addUser(User& user) { users.push_back(user); }

User* BookingSystem::getUserById(int userId) {
    for (auto& u : users) {
        if (u.getId() == userId) return &u;
    }
    return nullptr;
}

User* BookingSystem::getUserByPhone(const std::string& phone) {
    for (auto& user : users) {
        if (user.getPhone() == phone) {
            return &user;
        }
    }
    return nullptr;
}

bool BookingSystem::updateUserProfile(int userId,const std::string& newName,const std::string& newPhone) {
    for (auto& u : users) {
        if (u.getId() == userId) {
            if (!newName.empty())  u.setName(newName);
            if (!newPhone.empty()) u.setPhone(newPhone);
            saveToUserFile("data/users.txt");
            return true;
        }
    }
    return false;
}

//station
void BookingSystem::addStation(const std::string& name) 
{
    int newId=stations.size() + 1;
    stations.emplace_back(newId,name);
}

int BookingSystem::getStationCount() {
    return stations.size();
}

void BookingSystem::showAllStations() {
    if(stations.empty()) {
        std::cout<< "No stations available.\n";
        return;
    }
    for(auto& station:stations) {
        std::cout<< station.getId() <<". "<< station.getName() <<"\n";
    }
}

Station* BookingSystem::getStationById(int id) {
    for(auto& station:stations) {
        if(station.getId() == id) return &station;
    }
    return NULL;
}

int BookingSystem::getStationIdByName(const std::string& name) {
    for (auto& station : stations) {
        if (station.getName() == name)
            return station.getId();
    }
    return -1;
}

bool BookingSystem::renameStation(int stationId, const std::string& newName) {
    for (auto& station : stations) {
        if (station.getId() == stationId) {
            station.setName(newName);
            return true;
        }
    }
    return false;
}

bool BookingSystem::removeStation(int stationId) {
    std::vector<Train*> blockingTrains;
    for (auto& train : trains) {
        for (auto [id,dist] : train.getRoute()) {
            if (id == stationId) {
                blockingTrains.push_back(&train);
                break;
            }
        }
    }
    if (!blockingTrains.empty()) {
        std::cout << "\nStation is used in the following trains:\n";
        for (auto* t : blockingTrains) {
            std::cout << " - Train "
                      << t->getTrainNumber()
                      << " : "
                      << t->getTrainName()
                      << "\n";
        }
        std::cout << "\nDo you want to remove this station from ALL routes first? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            std::cout << "Station removal cancelled.\n";
            return false;
        }
        for (auto* t : blockingTrains) {
            t->removeStationFromRoute(stationId);
        }
        std::cout << "Station removed from all routes.\n";
    }
    for (auto it = stations.begin(); it != stations.end(); ++it) {
        if (it->getId() == stationId) {
            stations.erase(it);
            std::cout << "Station deleted successfully.\n";
            return true;
        }
    }
    return false;
}

//ticket
static std::string sanitizeFileName(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (std::isalnum(static_cast<unsigned char>(c)))
            out += c;
        else if (c == ' ')
            out += '_';
        // ignore other characters
    }
    if (out.empty()) out = "Passenger";
    return out;
}

std::string BookingSystem::getStationNameById(int stationId) {
    for (auto& s : stations) {
        if (s.getId() == stationId)
            return s.getName();
    }
    return "Unknown";
}

std::string BookingSystem::bookTicket(int userId,int trainNumber,const std::string& coachId,int fromIndex,int toIndex,
    const std::string& journeyDate,const std::string& passengerName,int passengerAge,const std::string& passengerGender
) {
    User* userPtr = nullptr;
    for (auto& u : users) {
        if (u.getId() == userId) {
            userPtr = &u;
            break;
        }
    }
    if (!userPtr) return "";
    for (auto& train : trains) {
        if (train.getTrainNumber() != trainNumber) continue;
        std::string trainName = train.getTrainName();
        auto& route = train.getRoute();
        if (fromIndex <= 0 || toIndex <= 0 ||
            fromIndex >= toIndex ||
            toIndex > static_cast<int>(route.size())) {
                return "";
        }
        auto& fromStop = route[fromIndex - 1];
        auto& toStop   = route[toIndex - 1];

        int distanceKm = toStop.kmFromStart - fromStop.kmFromStart;
        if (distanceKm <= 0)
            return "";

        std::string fromStation = getStationNameById(fromStop.stationId);
        std::string toStation = getStationNameById(toStop.stationId);

        for (auto& coach : train.getCoaches()) {
            if (coach.getCoachId() != coachId) continue;
            FareResult fareResult = FareCalculator::calculate( trainNumber, distanceKm, coachId, fareConfig );
            WLDataType wlEntry{
                userId,
                passengerName,
                passengerAge,
                passengerGender,
                fareResult
            };
            int seatNumber = coach.assignSeat(journeyDate);
            if (seatNumber == -1) {
                coach.addToWaitingList(journeyDate, wlEntry);
                return "WAITING";
            }
            std::string pnr = generatePNR(trainNumber, journeyDate);
            Ticket ticket(nextTicketId,pnr,trainNumber,trainName,coachId,seatNumber,userId,journeyDate,fromStation,toStation,        
                passengerName,passengerAge,passengerGender,fareResult,false
            );
            tickets.push_back(ticket);
            std::string safeName = sanitizeFileName(passengerName);
            std::string filePath = "data/ticket_" + pnr + "_" + safeName + ".html";

            tickets.back().generateHTML(filePath, userPtr->getName());
            nextTicketId++;
            saveToTicketFile("data/tickets.txt");
            return filePath;
        }
        return "";//Coach not found
    }
    return "";//Train not found
}

bool BookingSystem::cancelTicket(int ticketId,const std::string& journeyDate) {
    for (auto it = tickets.begin(); it != tickets.end(); ++it) {
        if (it->getTicketId() != ticketId) continue;
        if (it->getjourneyDate() != journeyDate)
            throw std::runtime_error("Journey date mismatch");

        int trainNumber = it->getTrainNumber();
        std::string coachId = it->getCoachId();
        int seatNumber = it->getSeatNumber();

        std::string oldPNR = it->getPnr();
        std::string oldPassenger = it->getPassengerName();

        for (auto& train : trains) {
            if (train.getTrainNumber() != trainNumber) continue;
            std::string trainName = train.getTrainName();

            for (auto& coach : train.getCoaches()) {
                if (coach.getCoachId() != coachId) continue;
                coach.releaseSeat(journeyDate, seatNumber);

                if (coach.hasWaiting(journeyDate)) {
                    WLDataType wl = coach.popFromWaitingList(journeyDate);

                    int newSeat = coach.assignSeat(journeyDate);
                    if (newSeat != -1) {
                        std::string newPNR = generatePNR(trainNumber, journeyDate);

                        auto& route = train.getRoute();
                        auto& fromStop = route.front();
                        auto& toStop   = route.back();

                        std::string fromStation = getStationNameById(fromStop.stationId);
                        std::string toStation = getStationNameById(toStop.stationId);

                        Ticket promoted(nextTicketId++,newPNR,trainNumber,trainName,coachId,newSeat,wl.userId,journeyDate,
                            fromStation,toStation,wl.passengerName,wl.passengerAge,wl.passengerGender,wl.fare,false
                        );
                        tickets.push_back(promoted);
                        std::string safeName = sanitizeFileName(wl.passengerName);
                        tickets.back().generateHTML(
                            "data/ticket_" + newPNR + "_" + safeName + ".html",
                            "SYSTEM"
                        );
                    }
                }
                std::string safeOldName = sanitizeFileName(oldPassenger);
                std::remove(
                    ("data/ticket_" + oldPNR + "_" + safeOldName + ".html").c_str()
                );
                tickets.erase(it);
                saveToTicketFile("data/tickets.txt");
                return true;
            }
        }
    }
    return false;
}

bool BookingSystem::cancelTicketByPNR(const std::string& pnr) {
    for(auto& ticket: tickets) { 
        if(ticket.getPnr() == pnr) return cancelTicket(ticket.getTicketId(),ticket.getjourneyDate());
    }
    return false;
}

void BookingSystem::showAllTickets() {
    for (auto& ticket : tickets)
    {
        ticket.displayTicket();
    }
}

Ticket* BookingSystem::findTicketById(int ticketId) {
    for(auto& ticket : tickets){
        if(ticket.getTicketId() == ticketId){
            return &ticket;
        }
    }
    return nullptr;
}

std::vector<Ticket> BookingSystem::getTicketByUser(int userId) {
    std::vector<Ticket> results;
    for(auto& ticket : tickets) {
        if(ticket.getUserId() == userId) {
            results.push_back(ticket);
        }
    }
    return results;
}

std::vector<Ticket> BookingSystem::getTicketByTrain(int trainNumber) {
    std::vector<Ticket> results;
    for(auto& ticket : tickets) {
        if(ticket.getTrainNumber() == trainNumber) {
            results.push_back(ticket);
        }
    }
    return results;
}

Ticket* BookingSystem::findTicketByPNR(const std::string& pnr) {
    for(auto& ticket:tickets){
        if(ticket.getPnr()==pnr) return &ticket;
    }
    return NULL;
}

//files
void BookingSystem::loadFromFile(const std::string &filename)
{
    tickets = Storage::loadTickets(filename);
    for (auto &t : tickets)
    {
        nextTicketId = std::max(nextTicketId, t.getTicketId() + 1);
        for (auto &train : trains)
        {
            if (train.getTrainNumber() == t.getTrainNumber())
            {
                train.bookSeat(t.getCoachId(), t.getSeatNumber());
            }
        }
    }
}

void BookingSystem::saveToTicketFile(const std::string& filename)
{
    Storage::saveTickets(tickets, filename);
}

void BookingSystem::saveToUserFile(const std::string& filename) {
    std::ofstream fout(filename, std::ios::trunc);
    if (!fout.is_open()) {
        std::cerr << "Error: Unable to open user file for writing.\n";
        return;
    }
    for (auto& user : users) {
        fout << user.getId() << " "
             << user.getName() << " "
             << user.getPhone() << "\n";
    }
    fout.close();
}

//Reports
void BookingSystem::showSystemSummary() {
    int activeTrains = 0;
    for (auto& t : trains) {
        if (t.isActive()) activeTrains++;
    }
    std::cout << "\n===== SYSTEM SUMMARY =====\n";
    std::cout << "Total Stations        : " << stations.size() << "\n";
    std::cout << "Total Trains          : " << trains.size() << "\n";
    std::cout << "Active Trains         : " << activeTrains << "\n";
    std::cout << "Inactive Trains       : " << trains.size() - activeTrains << "\n";
    std::cout << "Total Tickets Booked  : " << tickets.size() << "\n";
    std::cout << "Total Users           : " << users.size() << "\n";
}

void BookingSystem::showUserBookingReport(int userId) {
    std::cout << "\n===== USER BOOKING REPORT =====\n";
    User* user = nullptr;
    for (auto& u : users) {
        if (u.getId() == userId) {
            user = &u;
            break;
        }
    }
    if (!user) {
        std::cout << "User not found.\n";
        return;
    }
    std::cout << "User ID : " << user->getId() << "\n";
    std::cout << "Name    : " << user->getName() << "\n";
    std::cout << "--------------------------------\n";
    int count = 0;
    for (auto& t : tickets) {
        if (t.getUserId() == userId) {
            t.displayTicket();
            std::cout << "-------------------------------\n";
            count++;
        }
    }
    std::cout << "Total Tickets: " << count << "\n";
}

void BookingSystem::showTrainDetailedReport(int trainNumber,const std::string& journeyDate) {
    Train* train = nullptr;
    for (auto& t : trains) {
        if (t.getTrainNumber() == trainNumber) {
            train = &t;
            break;
        }
    }
    if (!train) {
        ConsoleStyle::setRed();
        std::cout << "Train not found.\n";
        ConsoleStyle::reset();
        return;
    }
    std::cout << "\n===== TRAIN DETAILED REPORT =====\n";
    std::cout << "Train Number : " << train->getTrainNumber() << "\n";
    std::cout << "Train Name   : " << train->getTrainName() << "\n";
    std::cout << "Status       : " 
              << (train->isActive() ? "ACTIVE" : "INACTIVE") << "\n\n";
    // Route
    std::cout << "Route:\n";
    for (auto [id,dist] : train->getRoute()) {
        Station* s = getStationById(id);
        if (s) std::cout << s->getName() << " -> ";
    }
    std::cout << "END\n\n";
    // Coach details
    std::cout << "Date: " << journeyDate << "\n\n";

    std::cout << std::left
            << std::setw(8)  << "Coach"
            << std::setw(15) << "Total Seats"
            << std::setw(15) << "Available"
            << "Status\n";

    std::cout << std::string(48, '-') << "\n";

    int totalTrainSeats = 0;
    int totalAvailableSeats = 0;
    int totalBookedTickets = 0;

    for (auto& coach : train->getCoaches()) {
        int total = coach.getTotalSeats();
        int booked = getBookedSeatsCount( train->getTrainNumber(),coach.getCoachId(),journeyDate );
        int available = total - booked;
        if (available < 0) available = 0;

        totalTrainSeats += total;
        totalAvailableSeats += available;
        totalBookedTickets += booked;
        std::string status = (available == 0 ? "FULL" : "OPEN");
        std::cout << std::left
                << std::setw(10)  << coach.getCoachId()
                << std::setw(15) << total
                << std::setw(14) << available
                << status << "\n";
    }
    std::cout << std::string(48, '-') << "\n";
    std::cout << "TOTAL SEATS      : " << totalTrainSeats << "\n";
    std::cout << "AVAILABLE SEATS  : " << totalAvailableSeats << "\n";
    std::cout << "BOOKED TICKETS   : " << totalBookedTickets << "\n";
}
