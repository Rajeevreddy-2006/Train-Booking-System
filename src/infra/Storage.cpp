#include "infra/Storage.h"
#include "domain/Ticket.h"
#include "domain/Station.h"
#include "domain/Train.h"
#include "domain/Coach.h"

#include <fstream>
#include <iostream>
#include <iomanip>   // for std::quoted

//tickets
bool Storage::saveTickets(std::vector<Ticket>& tickets,const std::string& filename){
    std::ofstream file(filename);
    if (!file) return false;
    for (auto& t : tickets) {
        FareResult& fare = t.getFareResult();
        file << t.getTicketId() << " "
             << t.getPnr() << " "
             << t.getTrainNumber() << " "
             << std::quoted(t.getTrainName()) << " "
             << t.getCoachId() << " "
             << t.getSeatNumber() << " "
             << t.getUserId() << " "
             << t.getjourneyDate() << " "
             << std::quoted(t.getFromStation()) << " "
             << std::quoted(t.getToStation()) << " "
             << std::quoted(t.getPassengerName()) << " "
             << t.getPassengerAge() << " "
             << t.getPassengerGender() << " "
             << t.getIsWaiting() << " "
             // Fare Breakdown
             << fare.baseFare << " "
             << fare.superfastCharge << " "
             << fare.reservationCharge << " "
             << fare.tatkalCharge << " "
             << fare.gst << " "
             << fare.discount << " "
             << fare.totalFare
             << "\n";
    }
    return true;
}

std::vector<Ticket> Storage::loadTickets(const std::string& filename){
    std::vector<Ticket> tickets;
    std::ifstream file(filename);
    if (!file) return tickets;
    int tid, trainNo, seat, userId, age;
    bool isWaiting;
    std::string pnr, trainName, coachId, date;
    std::string fromStation, toStation, name, gender;
    double baseFare, superfastCharge, reservationCharge,tatkalCharge, gst, discount, totalFare;
    while ( file >> tid >> pnr >> trainNo >> std::quoted(trainName) >> coachId >> seat >> userId >> date >> std::quoted(fromStation) 
                 >> std::quoted(toStation) >> std::quoted(name) >> age >> gender >> isWaiting >> baseFare >> superfastCharge
                 >> reservationCharge >> tatkalCharge >> gst >> discount >> totalFare ) {
        FareResult fare;
        fare.baseFare = baseFare;
        fare.superfastCharge = superfastCharge;
        fare.reservationCharge = reservationCharge;
        fare.tatkalCharge = tatkalCharge;
        fare.gst = gst;
        fare.discount = discount;
        fare.totalFare = totalFare;
        tickets.emplace_back(
            tid,pnr,trainNo,trainName,coachId,seat,userId,date,fromStation,toStation,name,age,gender,fare,isWaiting
        );
    }
    return tickets;
}

//stations
bool Storage::saveStations(std::vector<Station>& stations,const std::string& filename) {
    std::ofstream file(filename);
    if (!file) return false;

    for (auto& s : stations) {
        file << s.getId() << " " << std::quoted(s.getName()) << "\n";
    }
    return true;
}

std::vector<Station> Storage::loadStations(const std::string& filename) {
    std::vector<Station> stations;
    std::ifstream file(filename);
    if (!file) return stations;
    int id;
    std::string name;
    while (file >> id >> std::quoted(name)) {
        stations.emplace_back(id, name);
    }
    return stations;
}

//trains
/*
Train File Format:
TrainNumber "TrainName" TrainType ActiveStatus
- TrainType: 0 = Passenger, 1 = Express
- ActiveStatus: 0 = Inactive, 1 = Active
ROUTE stationId:kmFromStart,...,-1
COACH coachId totalSeats
END
*/
bool Storage::saveTrains(std::vector<Train>& trains,const std::string& filename){
    std::ofstream file(filename);
    if (!file) return false;
    for (auto& t : trains) {
        file << t.getTrainNumber() << " "
             << std::quoted(t.getTrainName()) << " "
             << static_cast<int>(t.getType()) << " "
             << t.isActive() << "\n";
        // ROUTE
        file << "ROUTE ";
        for (auto& stop : t.getRoute()) {
            file << stop.stationId << ":" << stop.kmFromStart << ",";
        }
        file << -1 << "\n";
        // COACHES
        for (auto& c : t.getCoaches()) {
            file << "COACH "
                 << c.getCoachId() << " "
                 << c.getTotalSeats() << "\n";
        }
        file << "END\n";
    }
    return true;
}
std::vector<Train> Storage::loadTrains(const std::string& filename){
    std::vector<Train> trains;
    std::ifstream file(filename);
    if (!file) return trains;
    int trainNo;
    std::string trainName;
    int typeInt;
    bool active;
    while (file >> trainNo >> std::quoted(trainName) >> typeInt >> active){
        TrainType type =
            (typeInt == 1) ? TrainType::Express
                           : TrainType::Passenger;

        Train train(trainNo, trainName, type);
        train.setActive(active);
        std::string token;
        while (file >> token) {
            if (token == "ROUTE") {
                std::string line;
                std::getline(file, line);
                std::stringstream ss(line);
                std::string part;
                while (std::getline(ss, part, ',')) {
                    if (part == "-1") break;
                    auto pos = part.find(':');
                    int stationId = std::stoi(part.substr(0, pos));
                    int kmFromStart = std::stoi(part.substr(pos + 1));
                    train.addRouteStop(stationId,kmFromStart);
                }
            }
            else if (token == "COACH") {
                std::string coachId;
                int seats;
                file >> coachId >> seats;
                train.addCoach(coachId, seats);
            }
            else if (token == "END") {
                break;
            }
        }
        trains.push_back(train);
    }
    return trains;
}

//users
bool Storage::saveUsers(std::vector<User>& users,const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    for (auto& user : users) {
        file << user.getId() << " "
             << std::quoted(user.getName()) << " "
             << user.getPhone() << "\n";
    }
    file.close();
    return true;
}

std::vector<User> Storage::loadUsers(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);

    int id;
    std::string name, phone;

    while (file >> id >> std::quoted(name) >> phone) {
        users.emplace_back(id, name, phone);
    }
    return users;
}

//fare config
bool Storage::saveFareConfig(const FareConfig& config,const std::string& filename){
    std::ofstream out(filename);
    if (!out) return false;

    out << "GST_PERCENT " << config.gstPercent << "\n";
    out << "DISCOUNT_PERCENT " << config.discountPercent << "\n\n";

    out << "SUPERFAST_CHARGE " << config.superfastCharge << "\n";
    out << "RESERVATION_CHARGE " << config.reservationCharge << "\n";
    out << "TATKAL_CHARGE " << config.tatkalCharge << "\n\n";

    out << "COACH_RATES\n";
    for (const auto& [coach, rate] : config.coachRatePerKm) {
        out << coach << " " << rate << "\n";
    }
    out << "END_COACH_RATES\n";

    return true;
}

bool Storage::loadFareConfig(FareConfig& config,const std::string& filename){
    std::ifstream in(filename);
    if (!in) return false;

    config.coachRatePerKm.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string key;
        ss >> key;
        if (key == "GST_PERCENT") {
            ss >> config.gstPercent;
        }
        else if (key == "DISCOUNT_PERCENT") {
            ss >> config.discountPercent;
        }
        else if (key == "SUPERFAST_CHARGE") {
            ss >> config.superfastCharge;
        }
        else if (key == "RESERVATION_CHARGE") {
            ss >> config.reservationCharge;
        }
        else if (key == "TATKAL_CHARGE") {
            ss >> config.tatkalCharge;
        }
        else if (key == "COACH_RATES") {
            while (std::getline(in, line) && line != "END_COACH_RATES"){
                std::stringstream cs(line);
                std::string coach;
                double rate;
                cs >> coach >> rate;
                config.coachRatePerKm[coach] = rate;
            }
        }
    }
    return true;
}
