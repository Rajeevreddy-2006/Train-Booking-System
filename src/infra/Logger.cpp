#include "infra/Logger.h"
#include <fstream>
#include <ctime>

static std::string currentTime()
{
    std::time_t now = std::time(nullptr);
    char buf[30];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}

void Logger::logBooking(const std::string& message)
{
    std::ofstream file("logs/booking.log", std::ios::app);
    if (!file.is_open()) return;

    file << "[" << currentTime() << "] "
         << "BOOKED | " << message << "\n";
}

void Logger::logCancel(const std::string& message)
{
    std::ofstream file("logs/cancel.log", std::ios::app);
    if (!file.is_open()) return;

    file << "[" << currentTime() << "] "
         << "CANCELLED | " << message << "\n";
}
