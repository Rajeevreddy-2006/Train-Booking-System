#ifndef STATION_H
#define STATION_H

#include <string>

class Station {
private:
    int id;
    std::string name;
public:
    Station(int id,const std::string& name);

    int getId();
    std::string& getName();
    void setName(const std::string& name);
};

#endif