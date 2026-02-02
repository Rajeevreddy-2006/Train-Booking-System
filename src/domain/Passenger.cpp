#include "domain/Passenger.h"
#include <iostream>

Passenger::Passenger(int id,const std::string& name,int age,const std::string& gender)
    : passengerId(id), name(name), age(age), gender(gender) {}

int Passenger::getId() {
    return passengerId;
}

std::string Passenger::getName() {
    return name;
}

int Passenger::getAge() {
    return age;
}

std::string Passenger::getGender() {
    return gender;
}

void Passenger::display() {
    std::cout << passengerId << " | "
              << name << " | "
              << age << " | "
              << gender << "\n";
}
