#include "ui/PassengerConsole.h"
#include "ui/ConsoleStyle.h"
#include "Authentication/PassengerAuth.h"
#include <iostream>

PassengerConsole::PassengerConsole(BookingSystem& system, int userid)
    : bookingSystem(system), userId(userid) {}

void PassengerConsole::start(BookingSystem& system) {
    while (true) {
        ConsoleStyle::clear();
        ConsoleStyle::header("Passenger Console");

        ConsoleStyle::menu({
            "View Trains & Routes",
            "Book Ticket",
            "My Tickets",
            "Cancel Ticket",
            "Profile",
            "Logout"
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

        switch (choice) {
            case 1: searchTrainsFlow(); break;
            case 2: bookTicketFlow(); break;
            case 3: showMyTicketsFlow(); break;
            case 4: cancelTicketFlow(); break;
            case 5: profileFlow(system); break;
            case 6: return; // logout
            default:
                ConsoleStyle::setRed();
                std::cout << "Invalid choice\n";
                ConsoleStyle::reset();
                ConsoleStyle::pause();
        }
    }
}

void PassengerConsole::searchTrainsFlow() {
    ConsoleStyle::clear();
    ConsoleStyle::header("Available Trains & Routes");
    bookingSystem.displayAllTrainsWithRoutes();

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
        Train* train = bookingSystem.getTrainByNumber(trainNumber);
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
            int booked = bookingSystem.getBookedSeatsCount( trainNumber, coach.getCoachId(), date );
            int available = total - booked;

            std::cout << coach.getCoachId()
                      << "  Available: " << available << "/" << total;

            if (available == 0) std::cout << "  (FULL)";
            std::cout << "\n";
        }
    }
    else {
        ConsoleStyle::setBlue();
        std::cout << "\nAlright! Feel free to browse anytime.\n";
        ConsoleStyle::reset();
    }
    ConsoleStyle::pause();
}

void PassengerConsole::bookTicketFlow() {
    ConsoleStyle::clear();
    ConsoleStyle::header("Book Ticket");

    bookingSystem.displayAllTrainsWithRoutes();

    int trainNumber;
    std::cout << "\nEnter Train Number: ";
    std::cin >> trainNumber;

    ConsoleStyle::clear();
    ConsoleStyle::header("Train Route");
    bookingSystem.TrainRoute(trainNumber);

    int fromIndex, toIndex;
    std::cout << "\nSelect FROM station (number): ";
    std::cin >> fromIndex;

    std::cout << "Select TO station (number): ";
    std::cin >> toIndex;
    if (fromIndex >= toIndex) {
        ConsoleStyle::setRed();
        std::cout << "Invalid route selection.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return;
    }

    std::string journeyDate;
    std::cout << "Enter Journey Date (YYYY-MM-DD): ";
    std::cin >> journeyDate;

    ConsoleStyle::clear();
    ConsoleStyle::header("Available Coaches");
    bookingSystem.displayTrainCoaches(trainNumber,journeyDate);

    std::string coachId;
    std::cout << "\nEnter Coach ID: ";
    std::cin >> coachId;

    int passengerCount;
    std::cout << "Number of passengers: ";
    std::cin >> passengerCount;

    for (int i = 1; i <= passengerCount; ++i) {
        std::string name, gender;
        int age;
        std::cout << "\nPassenger " << i << " Details\n";
        std::cout << "Name   : ";
        std::cin >> name;
        std::cout << "Age    : ";
        std::cin >> age;
        std::cout << "Gender : ";
        std::cin >> gender;
        std::string result = bookingSystem.bookTicket(
            userId, trainNumber, coachId, fromIndex, toIndex, journeyDate,
            name, age, gender
        );
        if (result.empty()) {
            std::cout << "Failed to book ticket for " << name << "\n";
        }
        else if (result == "WAITING") {
            std::cout << "No seats available. Added to waiting list.\n";
        }
        else {
            std::cout << "Ticket booked successfully for " << name << "\n";
            std::cout << "Ticket file generated at:\n";
            std::cout << result << "\n";
            char choice;
            std::cout << "Open ticket now? (y/n): ";
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                system(("start " + result).c_str());
            }
        }
    }
    ConsoleStyle::pause();
}

void PassengerConsole::showMyTicketsFlow() {
    ConsoleStyle::clear();
    ConsoleStyle::header("My Tickets");
    auto tickets = bookingSystem.getTicketByUser(userId);
    if (tickets.empty()) {
        std::cout << "You have no tickets booked.\n";
        ConsoleStyle::pause();
        return;
    }
    for (auto& ticket : tickets) {
        std::cout << "--------------------------------------\n";
        std::cout << "Ticket ID  : " << ticket.getTicketId() << "\n";
        std::cout << "PNR        : " << ticket.getPnr() << "\n";
        std::cout << "Passenger  : " << ticket.getPassengerName()
                  << " (" << ticket.getPassengerAge()
                  << ", " << ticket.getPassengerGender() << ")\n";
        std::cout << "Train No   : " << ticket.getTrainNumber() << "\n";
        std::cout << "Coach      : " << ticket.getCoachId() << "\n";
        std::cout << "Seat No    : " << ticket.getSeatNumber() << "\n";
        std::cout << "Journey    : " << ticket.getjourneyDate() << "\n";
        std::cout << "Total fare : " << ticket.getTotalFare() << "\n";
    }
    std::cout << "--------------------------------------\n";
    ConsoleStyle::pause();
}

void PassengerConsole::cancelTicketFlow() {
    ConsoleStyle::clear();
    ConsoleStyle::header("Cancel Ticket");
    std::string pnr;
    std::cout << "Enter PNR (0 to go back): ";
    std::cin >> pnr;
    if (pnr == "0") {
        return;
    }
    char confirm;
    std::cout << "Are you sure you want to cancel this ticket? (y/n): ";
    std::cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        ConsoleStyle::setRed();
        std::cout << "Cancellation aborted.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return;
    }
    if (bookingSystem.cancelTicketByPNR(pnr)) {
        ConsoleStyle::setGreen();
        std::cout << "Ticket cancelled successfully.\n";
        ConsoleStyle::reset();
    } else {
        ConsoleStyle::setRed();
        std::cout << "Invalid PNR. No ticket found.\n";
        ConsoleStyle::reset();
    }
    ConsoleStyle::pause();
}

void PassengerConsole::profileFlow(BookingSystem& system) {
    while (true) {
        ConsoleStyle::clear();
        ConsoleStyle::header("My Profile");
        ConsoleStyle::menu({
            "View Profile",
            "Change Name",
            "Change Phone",
            "Change Password",
            "Back"
        });

        std::cout << "\nChoose option: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            ConsoleStyle::pause();
            continue;
        }
        if (choice == 1) { // View Profile
            User* user = bookingSystem.getUserById(userId);
            if (!user) {
                std::cout << "User not found.\n";
            } else {
                std::cout << "\n--- Profile Details ---\n";
                std::cout << "User ID : " << user->getId() << "\n";
                std::cout << "Name    : " << user->getName() << "\n";
                std::cout << "Phone   : " << user->getPhone() << "\n";
            }
            ConsoleStyle::pause();
        }
        else if (choice == 2) { // Change Name
            std::string newName;
            std::cout << "Enter new name: ";
            std::cin.ignore();
            std::getline(std::cin, newName);
            if (newName.empty()) {
                std::cout << "Name cannot be empty.\n";
            } else if (bookingSystem.updateUserProfile(userId, newName, "")) {
                std::cout << "Name updated successfully.\n";
            } else {
                std::cout << "Failed to update name.\n";
            }
            ConsoleStyle::pause();
        }
        else if (choice == 3) { // Change Phone
            std::string newPhone;
            std::cout << "Enter new phone: ";
            std::cin >> newPhone;
            if (newPhone.empty()) {
                std::cout << "Phone cannot be empty.\n";
            } else if (bookingSystem.updateUserProfile(userId, "", newPhone)) {
                std::cout << "Phone updated successfully.\n";
            } else {
                std::cout << "Failed to update phone.\n";
            }
            ConsoleStyle::pause();
        }
        else if (choice == 4) { // Change Password
            if (PassengerAuth::changePassword(system,userId)) {
                std::cout << "Password changed successfully.\n";
            } else {
                std::cout << "Password change failed.\n";
            }
            ConsoleStyle::pause();
        }
        else return;
    }
}