#include "infra/Storage.h"
#include "domain/Ticket.h"
#include "domain/Station.h"
#include "domain/Train.h"
#include "domain/Coach.h"

#include <fstream>
#include <iostream>
#include <iomanip>   // for std::quoted

//tickets
bool Storage::saveTickets(std::vector<Ticket>& tickets,const std::string& filename) {
    std::ofstream file(filename);
    if (!file) return false;
    for (const auto& t : tickets) {
        const FareResult& fare = t.getFareResult();
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
             << fare.baseFare << " "
             << fare.trainCharge << " "
             << fare.gstAmount << " "
             << fare.discountAmount << " "
             << fare.totalFare
             << "\n";
    }
    return true;
}

std::vector<Ticket> Storage::loadTickets(const std::string& filename) {
    std::vector<Ticket> tickets;
    std::ifstream file(filename);
    if (!file) return tickets;

    int tid, trainNo, seat, userId, age;
    bool isWaiting;
    std::string pnr, trainName, coachId, date;
    std::string fromStation, toStation, name, gender;
    double baseFare, trainCharge, gstAmount, discountAmount, totalFare;

    while ( file >> tid >> pnr >> trainNo >> std::quoted(trainName) >> coachId >> seat >> userId >> date
                 >> std::quoted(fromStation) >> std::quoted(toStation) >> std::quoted(name) >> age >> gender >> isWaiting
                 >> baseFare >> trainCharge >> gstAmount >> discountAmount >> totalFare ) {
        FareResult fare;
        fare.baseFare       = baseFare;
        fare.trainCharge    = trainCharge;
        fare.gstAmount      = gstAmount;
        fare.discountAmount = discountAmount;
        fare.totalFare      = totalFare;
        tickets.emplace_back(
            tid,pnr,trainNo,trainName,coachId,seat,userId,date,
            fromStation,toStation,name,age,gender,fare,isWaiting
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
 Format:
 TrainNumber TrainName Active
 ROUTE stationId stationId ... -1
 COACH coachType seats
 END
*/

bool Storage::saveTrains(std::vector<Train>& trains,const std::string& filename) {
    std::ofstream file(filename);
    if (!file) return false;
    for (auto& t : trains) {
        file << t.getTrainNumber() << " "
             << std::quoted(t.getTrainName()) << " "
             << t.isActive() << "\n";
        // Route
        file << "ROUTE ";
        for (auto& stop : t.getRoute()) {
            file << stop.stationId << ":" << stop.kmFromStart << ",";
        }
        file << -1 << "\n";
        // Coaches
        for (auto& c : t.getCoaches()) {
            file << "COACH "
                 << c.getCoachId() << " "
                 << c.getTotalSeats() << "\n";
        }
        file << "END\n";
    }
    return true;
}

std::vector<Train> Storage::loadTrains(const std::string& filename) {
    std::vector<Train> trains;
    std::ifstream file(filename);
    if (!file) return trains;

    int trainNo;
    std::string trainName;
    bool active;

    while (file >> trainNo >> std::quoted(trainName) >> active) {
        Train train(trainNo, trainName);
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
                    train.addRouteStop(stationId, kmFromStart);
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
bool Storage::saveFareConfig(const FareConfig& config,const std::string& filename) {
    std::ofstream out(filename);
    if (!out) return false;

    out << "GST_PERCENT " << config.gstPercent << "\n";
    out << "DISCOUNT_PERCENT " << config.discountPercent << "\n\n";

    out << "COACH_RATES\n";
    for (const auto& [coach, rate] : config.coachRatePerKm) {
        out << coach << " " << rate << "\n";
    }
    out << "END_COACH_RATES\n\n";

    out << "TRAIN_CHARGES\n";
    for (const auto& [trainNo, charge] : config.trainCharge) {
        out << trainNo << " " << charge << "\n";
    }
    out << "END_TRAIN_CHARGES\n";

    return true;
}

bool Storage::loadFareConfig(FareConfig& config,const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;

    config.coachRatePerKm.clear();
    config.trainCharge.clear();

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
        else if (key == "COACH_RATES") {
            while (std::getline(in, line) && line != "END_COACH_RATES") {
                std::stringstream cs(line);
                std::string coach;
                double rate;
                cs >> coach >> rate;
                config.coachRatePerKm[coach] = rate;
            }
        }
        else if (key == "TRAIN_CHARGES") {
            while (std::getline(in, line) && line != "END_TRAIN_CHARGES") {
                std::stringstream ts(line);
                int trainNo;
                double charge;
                ts >> trainNo >> charge;
                config.trainCharge[trainNo] = charge;
            }
        }
    }
    return true;
}
