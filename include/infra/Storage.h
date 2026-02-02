#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

#include "domain/Ticket.h"
#include "domain/Station.h"
#include "domain/Train.h"
#include "domain/User.h"
#include "domain/FareConfig.h"

class Storage {
public:
    //tickets
    static bool saveTickets(std::vector<Ticket>& tickets,const std::string& filename);
    static std::vector<Ticket> loadTickets(const std::string& filename);

    //stations
    static bool saveStations(std::vector<Station>& stations,const std::string& filename);
    static std::vector<Station> loadStations(const std::string& filename);

    //trains (basic + route + coaches)
    static bool saveTrains(std::vector<Train>& trains,const std::string& filename);
    static std::vector<Train> loadTrains(const std::string& filename);

    //users
    static bool saveUsers(std::vector<User>& users,const std::string& filename);
    static std::vector<User> loadUsers(const std::string& filename);

    //fare config
    static bool saveFareConfig(const FareConfig& config,const std::string& filename);
    static bool loadFareConfig(FareConfig& config,const std::string& filename);
};

#endif
