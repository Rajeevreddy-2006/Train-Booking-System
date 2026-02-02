#include "ui/ConsoleStyle.h"
#include "ui/AdminConsole.h"
#include "ui/InputHelper.h"
#include "Authentication/PasswordUtil.h"

#include <iostream>
#include <fstream>

const std::string STAFF_FILE = "data/staff.txt";
//staff 
void AdminConsole::addStaffFlow() {
    std::string name, phone, password;
    std::cin.ignore();

    std::cout << "Staff name: ";
    std::getline(std::cin, name);

    bool exists = false;
    {
        std::ifstream in("data/staff.txt");
        std::string line;
        while (std::getline(in, line)) {
            // name|phone|password
            int pos = line.find('|');
            if (pos == std::string::npos) continue;
            std::string existingName = line.substr(0, pos);
            if (existingName == name) {
                exists = true;
                break;
            }
        }
    }
    if (exists) {
        std::cout << "Staff already exists\n";
        ConsoleStyle::pause();
        return;
    }

    std::cout << "Phone Number: ";
    std::getline(std::cin, phone);

    std::cout << "Password: ";
    password = readPassword();
    std::string hashpass=hashPassword(password);

    std::ofstream out(STAFF_FILE, std::ios::app);
    out << name << "|" << phone << "|" << hashpass << "\n";

    ConsoleStyle::setGreen();
    std::cout << "Staff added successfully\n";
    ConsoleStyle::reset();
    ConsoleStyle::pause();
}

void AdminConsole::viewStaffListFlow() {
    std::ifstream in(STAFF_FILE);
    std::string line;
    ConsoleStyle::clear();
    ConsoleStyle::header("Staff List");

    while (std::getline(in, line)) {
        auto pos1 = line.find('|');
        auto pos2 = line.rfind('|');

        std::string name = line.substr(0, pos1);
        std::string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);

        std::cout << "Name: " << name
                  << " | Phone: " << phone << "\n";
    }
    ConsoleStyle::pause();
}

void AdminConsole::resetStaffPasswordFlow() {
    std::string name, newPwd;
    std::cin.ignore();
    std::cout << "Staff name: ";
    std::getline(std::cin, name);
    std::cout << "New password: ";
    newPwd = readPassword();
    std::string newhashpass=hashPassword(newPwd);

    std::ifstream in(STAFF_FILE);
    std::ofstream out("data/temp.txt");
    std::string line;
    bool found = false;
    while (std::getline(in, line)) {
        auto pos1 = line.find('|');
        auto pos2 = line.rfind('|');
        std::string n = line.substr(0, pos1);
        std::string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
        if (n == name) {
            out << n << "|" << phone << "|" << newhashpass << "\n";
            found = true;
        } else {
            out << line << "\n";
        }
    }
    in.close();
    out.close();
    std::remove(STAFF_FILE.c_str());
    std::rename("data/temp.txt", STAFF_FILE.c_str());

    if (found){
        ConsoleStyle::setGreen();
        std::cout << "Password reset successfully\n";
        ConsoleStyle::reset();
    }else{
        ConsoleStyle::setRed();
        std::cout << "Staff not found\n";
        ConsoleStyle::reset();
    }
    ConsoleStyle::pause();
}

void AdminConsole::removeStaffFlow() {
    std::string name;
    std::cin.ignore();
    std::cout << "Staff name to remove: ";
    std::getline(std::cin, name);
    char c;
    std::cout << "Confirm (y/n): ";
    std::cin >> c;
    if (c != 'y' && c != 'Y') return;

    std::ifstream in(STAFF_FILE);
    std::ofstream out("data/temp.txt");
    std::string line;
    bool removed = false;
    while (std::getline(in, line)) {
        if (line.substr(0, line.find('|')) != name)
            out << line << "\n";
        else
            removed = true;
    }
    in.close();
    out.close();
    std::remove(STAFF_FILE.c_str());
    std::rename("data/temp.txt", STAFF_FILE.c_str());

    std::cout << (removed ? "Staff removed\n" : "Staff not found\n");
    ConsoleStyle::pause();
}

void AdminConsole::viewProfileFlow(const std::string& staffName) {
    std::ifstream in(STAFF_FILE);
    std::string line;
    while (std::getline(in, line)) {
        auto pos1 = line.find('|');
        auto pos2 = line.rfind('|');
        std::string name = line.substr(0, pos1);
        if (name == staffName) {
            std::string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            ConsoleStyle::header("My Profile");
            std::cout << "Name  : " << name << "\n";
            std::cout << "Phone : " << phone << "\n";
            std::cout << "Role  : STAFF\n";
            ConsoleStyle::pause();
            return;
        }
    }
}

//stations flow
void AdminConsole::addStationFlow(BookingSystem& system) {
    ConsoleStyle::clear();
    ConsoleStyle::header("ADD STATION");

    std::string name;
    std::cout << "Enter station name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    system.addStation(name);

    std::cout << "\nStation added successfully.\n";
    ConsoleStyle::pause();
}

void AdminConsole::viewStationsFlow(BookingSystem& system) {
    ConsoleStyle::clear();
    ConsoleStyle::header("ALL STATIONS");

    system.showAllStations();
    ConsoleStyle::pause();
}

void AdminConsole::renameStationFlow(BookingSystem& system) {
    ConsoleStyle::clear();
    ConsoleStyle::header("RENAME STATION");

    system.showAllStations();

    int id;
    std::cout << "\nEnter station ID: ";
    std::cin >> id;

    std::string newName;
    std::cout << "Enter new name: ";
    std::cin.ignore();
    std::getline(std::cin, newName);

    if (system.renameStation(id, newName))
        std::cout << "\nStation renamed successfully.\n";
    else
        std::cout << "\nInvalid station ID.\n";

    ConsoleStyle::pause();
}

void AdminConsole::removeStationFlow(BookingSystem& system) {
    ConsoleStyle::clear();
    ConsoleStyle::header("REMOVE STATION");

    system.showAllStations();

    int id;
    std::cout << "\nEnter station ID: ";
    std::cin >> id;

    if (system.removeStation(id))
        std::cout << "\nStation removed successfully.\n";
    else
        std::cout << "\nInvalid station ID.\n";

    ConsoleStyle::pause();
}

//trains flow
void AdminConsole::addTrainFlow(BookingSystem& system) {
    int trainNo;
    std::string name;

    std::cout << "Enter train number: ";
    std::cin >> trainNo;

    std::cout << "Enter train name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    system.addTrain(trainNo, name);

    std::cout << "Train added successfully\n";
    ConsoleStyle::pause();
}

void AdminConsole::viewTrainsFlow(BookingSystem& system,const std::string& date) {
    system.displayAllTrains(date);
    ConsoleStyle::pause();
}

void AdminConsole::removeTrainFlow(BookingSystem& system) {
    int no;
    std::cout << "Enter Train Number to remove: ";
    std::cin >> no;

    if (system.removeTrain(no))
        std::cout << "Train removed successfully.\n";
    else
        std::cout << "Train not found.\n";

    ConsoleStyle::pause();
}

void AdminConsole::toggleTrainStatusFlow(BookingSystem& system) {
    int no;
    std::cout << "Enter Train Number: ";
    std::cin >> no;

    if (system.toggleTrainStatus(no))
        std::cout << "Train status updated.\n";
    else
        std::cout << "Train not found.\n";

    ConsoleStyle::pause();
}

//coach flow
void AdminConsole::addCoachFlow(BookingSystem& system) {
    int trainNo;
    std::string coachId;
    int seats;

    std::cout << "Enter Train Number: ";
    std::cin >> trainNo;

    std::cout << "Enter Coach Type (GEN / SL / AC3 / AC2 / AC1 / CC): ";
    std::cin >> coachId;

    std::cout << "Enter Number of Seats: ";
    std::cin >> seats;

    if (system.addCoachToTrain(trainNo, coachId, seats))
        std::cout << "Coach added successfully.\n";
    else
        std::cout << "Failed to add coach (Train not found / Duplicate coach).\n";

    ConsoleStyle::pause();
}

void AdminConsole::removeCoachFlow(BookingSystem& system) {
    int trainNo;
    std::string coachId;

    std::cout << "Enter Train Number: ";
    std::cin >> trainNo;

    std::cout << "Enter Coach Type to remove: ";
    std::cin >> coachId;

    if (system.removeCoachFromTrain(trainNo, coachId))
        std::cout << "Coach removed successfully.\n";
    else
        std::cout << "Coach not found.\n";

    ConsoleStyle::pause();
}

void AdminConsole::updateCoachSeatsFlow(BookingSystem& system) {
    int trainNo;
    std::string coachId;
    int newSeats;

    std::cout << "Enter Train Number: ";
    std::cin >> trainNo;

    std::cout << "Enter Coach Type: ";
    std::cin >> coachId;

    std::cout << "Enter New Seat Count: ";
    std::cin >> newSeats;

    if (system.updateCoachSeats(trainNo, coachId, newSeats))
        std::cout << "Coach seats updated.\n";
    else
        std::cout << "Update failed.\n";

    ConsoleStyle::pause();
}

void AdminConsole::viewTrainCoachesFlow(BookingSystem& system) {
    int trainNo;
    std::cout << "Enter Train Number: ";
    std::cin >> trainNo;

    std::string journeyDate;
    std::cout << "Enter Date to View (YYYY-MM-DD): ";
    std::cin >> journeyDate;

    system.displayTrainCoaches(trainNo,journeyDate);
    ConsoleStyle::pause();
}