#include "ui/EntryConsole.h"
#include "ui/ConsoleStyle.h"
#include "ui/AdminConsole.h"
#include "ui/PassengerConsole.h"
#include "ui/GuestConsole.h"
#include "ui/PassengerPortal.h"

#include <iostream>

void EntryConsole::run(BookingSystem& system) {
    while (true) {
        ConsoleStyle::clear();
        ConsoleStyle::mainheader("Railway Management & Reservation System");

        ConsoleStyle::menu({
            "Admin Panel",
            "Passenger Portal",
            "Guest View",
            "Exit"
        });

        std::cout << "\nChoose option: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            ConsoleStyle::setRed();
            std::cout << "Invalid input. Numbers only.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            continue;
        }

        switch (choice) {
            case 1:
                AdminConsole::run(system);
                break;
            case 2:
            {
                PassengerPortal portal(system);
                portal.start();
                break;
            }
            case 3:
                GuestConsole::run(system);
                break;
            case 4: {
                char confirm;
                std::cout << "Are you sure you want to exit? (y/n): ";
                std::cin >> confirm;
                if (confirm == 'y' || confirm == 'Y')
                    return;
                break;
            }
            default:
                std::cout << "Invalid choice\n";
                ConsoleStyle::pause();
        }
    }
}

