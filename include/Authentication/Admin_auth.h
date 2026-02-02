#ifndef ADMIN_AUTH_H
#define ADMIN_AUTH_H

#include <string>

enum class AdminRole {
    HEAD,
    STAFF
};

class AdminAuth {
public:
    static bool loginHead(const std::string& password);
    static bool loginStaff(const std::string& username,const std::string& password);
};

#endif
//static means the function belongs to the class, not to an object.
//(compile-time scope)Namespaces prevent name conflicts and logically group functions without requiring objects.