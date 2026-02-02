#include "ui/PassengerPortal.h"
#include "Authentication/PassengerAuth.h"
#include "ui/PassengerConsole.h"
#include "ui/ConsoleStyle.h"
#include <iostream>

PassengerPortal::PassengerPortal(BookingSystem& system)
    : bookingSystem(system) {}

void PassengerPortal::start() {
    while (true) {
        ConsoleStyle::clear();
        ConsoleStyle::header("Passenger Portal");

        ConsoleStyle::menu({
            "Login",
            "Create Account",
            "Back"
        });

        std::cout << "\nChoose option: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            ConsoleStyle::setRed();
            std::cout << "Invalid input.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            continue;
        }

        if (choice == 1) {
            // LOGIN
            int userId = PassengerAuth::login(bookingSystem);
            if (userId != -1) {
                PassengerConsole pc(bookingSystem, userId);
                pc.start(bookingSystem);          // passenger menu loop
            }
        }
        else if (choice == 2) {
            // REGISTER
            int userId = PassengerAuth::registerUser(bookingSystem);
            if (userId != -1) {
                PassengerConsole pc(bookingSystem, userId);
                pc.start(bookingSystem);
            }
        }
        else if (choice == 3) {
            // BACK to EntryConsole
            return;
        }
        else {
            ConsoleStyle::setRed();
            std::cout << "Invalid choice.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
        }
    }
}
