#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

class Passenger {
private:
    int passengerId;
    std::string name;
    int age;
    std::string gender;

public:
    Passenger(int id,const std::string& name,int age,const std::string& gender);

    int getId();
    std::string getName();
    int getAge();
    std::string getGender();

    void display();
};

#endif
