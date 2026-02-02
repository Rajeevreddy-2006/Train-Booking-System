#include "domain/Station.h"

Station::Station(int id,const std::string& name): id(id),name(name) {}

int Station::getId() {
    return id;
}

std::string& Station::getName() {
    return name;
}

void Station::setName(const std::string& name) {
    this->name =name;
}