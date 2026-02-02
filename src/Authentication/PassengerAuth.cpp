#include "Authentication/PassengerAuth.h"
#include "Authentication/PasswordUtil.h"
#include "ui/ConsoleStyle.h"
#include "ui/InputHelper.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <limits>

#define AUTH_FILE "data/passengers_auth.txt"

int PassengerAuth::login(BookingSystem& system) {
    std::string phone, password;
    std::cout << "\n--- Passenger Login ---\n";
    std::cout << "Phone: ";
    std::cin >> phone;

    std::cout << "Password: ";
    password = readPassword();

    std::ifstream file(AUTH_FILE);
    if (!file.is_open()) {
        ConsoleStyle::setRed();
        std::cout << "Auth file not found.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return -1;
    }

    int userId;
    std::string storedPhone, storedHash;
    std::string inputHash = hashPassword(password);

    while (file >> userId >> storedPhone >> storedHash) {
        if (storedPhone == phone && storedHash == inputHash) {
            if (!system.getUserById(userId)) {
                ConsoleStyle::setRed();
                std::cout << "User profile missing. Contact admin.\n";
                ConsoleStyle::reset();
                ConsoleStyle::pause();
                return -1;
            }
            ConsoleStyle::setGreen();
            std::cout << "Login successful.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            return userId;
        }
    }
    ConsoleStyle::setRed();
    std::cout << "Invalid phone or password.\n";
    ConsoleStyle::reset();
    ConsoleStyle::pause();
    return -1;
}

int PassengerAuth::registerUser(BookingSystem& system) {
    std::string name, phone, password;

    std::cout << "\n--- Create Passenger Account ---\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Phone: ";
    std::cin >> phone;

    if (system.getUserByPhone(phone)) {
        ConsoleStyle::setRed();
        std::cout << "Phone already registered.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return -1;
    }

    std::cout << "Set Password: ";
    password = readPassword();

    int id;
    std::string u, p;
    int newUserId = 1; // Generate new userId
    std::ifstream readFile(AUTH_FILE);
    while (readFile >> id >> u >> p) {
        newUserId = id + 1;
    }
    readFile.close();

    User user(newUserId, name, phone);
    system.addUser(user);
    system.saveToUserFile("data/users.txt");

    std::ofstream out(AUTH_FILE, std::ios::app);// Save new user
    out << newUserId << " "
        << phone << " "
        << hashPassword(password) << "\n";
    out.close();
    
    ConsoleStyle::setGreen();
    std::cout << "Account created successfully.\n";
    ConsoleStyle::reset();
    ConsoleStyle::pause();
    return newUserId;
}

bool PassengerAuth::changePassword(BookingSystem& system, int userId) {
    std::string oldPass, newPass;
    std::cout << "Enter current password: ";
    oldPass = readPassword();
    std::ifstream in(AUTH_FILE);
    if (!in.is_open()) {
        ConsoleStyle::setRed();
        std::cout << "Auth file not found.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return false;
    }
    std::vector<std::tuple<int, std::string, std::string>> records;
    int id;
    std::string phone, hash;
    bool found = false;
    while (in >> id >> phone >> hash) {
        if (id == userId) {
            if (hash != hashPassword(oldPass)) {
                ConsoleStyle::setRed();
                std::cout << "Incorrect password.\n";
                ConsoleStyle::reset();
                ConsoleStyle::pause();
                return false;
            }
            found = true;
            records.emplace_back(id, phone, "");
        } else {
            records.emplace_back(id, phone, hash);
        }
    }
    in.close();
    if (!found) {
        ConsoleStyle::setRed();
        std::cout << "User not found.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return false;
    }
    std::cout << "Enter new password: ";
    newPass = readPassword();
    std::string newHash = hashPassword(newPass);
    std::ofstream out(AUTH_FILE, std::ios::trunc);
    for (auto& r : records) {
        out << std::get<0>(r) << " "
            << std::get<1>(r) << " "
            << (std::get<2>(r).empty() ? newHash : std::get<2>(r))
            << "\n";
    }
    out.close();

    ConsoleStyle::setGreen();
    std::cout << "Password updated successfully.\n";
    ConsoleStyle::reset();
    ConsoleStyle::pause();
    return true;
}

