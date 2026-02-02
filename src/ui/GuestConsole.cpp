#include "ui/GuestConsole.h"
#include "ui/ConsoleStyle.h"
#include <iostream>

void GuestConsole::run(BookingSystem& system) {
    while(true){
        ConsoleStyle::clear();
        ConsoleStyle::header("Guest Console");

        ConsoleStyle::menu({
            "View Trains",
            "View Stations",
            "Back"
        });

        std::cout << "\nChoose option: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            ConsoleStyle::setRed();
            std::cout << "Invalid input. Numbers only.\n";
            ConsoleStyle::reset();
            
            std::cin.ignore(1000, '\n');
            ConsoleStyle::pause();
            continue;
        }

        switch (choice) {
            case 1:
                searchTrainsFlow(system);
                break;
            case 2:
                system.showAllStations();
                ConsoleStyle::pause();
                break;
            case 3:
                return;
            default:
                std::cout << "Invalid choice\n";
        }
    }
}

void GuestConsole::searchTrainsFlow(BookingSystem& system) {
    ConsoleStyle::clear();
    ConsoleStyle::header("Available Trains & Routes");
    system.displayAllTrainsWithRoutes();

    char choice;
    std::cout << "\nDo you want to check seat availability for a train? (y/n): ";
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        ConsoleStyle::setRed();
        std::cout << "Invalid input.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
    }

    if (choice == 'y' || choice == 'Y') {
        int trainNumber;
        std::cout << "Enter Train Number: ";
        std::cin >> trainNumber;

        std::string date;
        std::cout << "Enter Journey Date (YYYY-MM-DD): ";
        std::cin >> date;

        ConsoleStyle::clear();
        ConsoleStyle::header("Coach Availability");
        Train* train = system.getTrainByNumber(trainNumber);
        if (!train) {
            ConsoleStyle::setRed();
            std::cout << "Train not found.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            return;
        }
        std::cout << "\nTrain: " << trainNumber
                  << " | Date: " << date << "\n\n";

        for (auto& coach : train->getCoaches()) {
            int total = coach.getTotalSeats();
            int booked = system.getBookedSeatsCount( trainNumber, coach.getCoachId(), date );
            int available = total - booked;

            std::cout << coach.getCoachId()
                      << "  Available: " << available << "/" << total;

            if (available == 0) std::cout << "  (FULL)";
            std::cout << "\n";
        }
        ConsoleStyle::pause();
    }
    else if (choice == 'n' || choice == 'N') {
        ConsoleStyle::setYellow();
        std::cout << "\nReturning to main menu...\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return;
    }
    else {
        ConsoleStyle::setRed();
        std::cout << "\nInvalid choice. Please enter y or n.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return;
    }
}