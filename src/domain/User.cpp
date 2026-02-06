#include "domain/User.h"

User::User(int id, const std::string& name, const std::string& phone)
    : userId(id), name(name), phone(phone) {}

int User::getId() { return userId; }

std::string User::getName() { return name; }

std::string User::getPhone() { return phone; }

void User::setName(const std::string& name) { this->name = name; }

void User::setPhone(const std::string& phone) { this->phone = phone; }

void User::addPassenger(Passenger& p) { savedPassengers.push_back(p); }

std::vector<Passenger>& User::getPassengers() { return savedPassengers; }
