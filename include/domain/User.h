#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "domain/Passenger.h"

class User {
private:
    int userId;
    std::string name;
    std::string phone;
    std::vector<Passenger> savedPassengers;

public:
    User(int id, const std::string& name, const std::string& phone);

    int getId();
    std::string getName();
    std::string getPhone();
    void setName(const std::string& name);
    void setPhone(const std::string& phone);

    // Passenger management
    void addPassenger(Passenger& p);
    std::vector<Passenger>& getPassengers();
};

#endif
