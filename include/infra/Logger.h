#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    static void logBooking(const std::string& message);
    static void logCancel(const std::string& message);
};

#endif