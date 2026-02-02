#ifndef PASSWORD_UTIL_H
#define PASSWORD_UTIL_H

#include <string>

std::string hashPassword(const std::string& password); 

#endif
//const-A compile-time safety guard