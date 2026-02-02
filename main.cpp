#include "ui/EntryConsole.h"
#include "ui/ConsoleStyle.h"
#include "core/BookingSystem.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    BookingSystem system;

    // Load ALL data (stations, trains, tickets)
    system.loadAll();

    ConsoleStyle::clear();
    //ConsoleStyle::setGreen();
    ConsoleStyle::banner();
    ConsoleStyle::reset();
    std::cout << "\nWelcome to RailNest 🚆\n";
    ConsoleStyle::pause();

    // Start application
    EntryConsole::run(system);

    // Save ALL data
    system.saveAll();

    ConsoleStyle::clear();
    //ConsoleStyle::setBlue();
    ConsoleStyle::showEnd();
    std::cout << "Thank you for using RailNest 🚆\n";
    std::cout << "Simple • Secure • Scalable Console App\n";
    ConsoleStyle::reset();

    return 0;
}
