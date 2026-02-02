#include "Authentication/Admin_auth.h"
#include "Authentication/PasswordUtil.h"
#include <fstream>
#include <string>

bool AdminAuth::loginHead(const std::string& password) {
    std::hash<std::string> hasher;
    std::string hased=std::to_string(hasher(password));
    std::string storedPassword=std::to_string(hasher("Head@123"));
    return storedPassword == hased;
}

bool AdminAuth::loginStaff(const std::string& username,const std::string& password) {
    std::ifstream file("data/staff.txt");
    if (!file) return false;

    std::string enteredHash = hashPassword(password);

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        //format: name|phone|hash
        int p1 = line.find('|');
        if (p1 == std::string::npos) continue;

        int p2 = line.find('|', p1 + 1);
        if (p2 == std::string::npos) continue;

        std::string u = line.substr(0, p1);
        std::string phone = line.substr(p1 + 1, p2 - p1 - 1);
        std::string storedHash = line.substr(p2 + 1);

        if (u == username && storedHash == enteredHash) {
            return true;
        }
    }
    return false;
}
