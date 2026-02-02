#include "Authentication/PasswordUtil.h"
#include <functional>

std::string hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}
