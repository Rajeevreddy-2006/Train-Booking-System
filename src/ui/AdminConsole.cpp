#include "ui/AdminConsole.h"
#include "ui/ConsoleStyle.h"
#include "ui/InputHelper.h"
#include "Authentication/Admin_auth.h"
#include <iostream>
#include <limits>

void AdminConsole::run(BookingSystem& system) {
    ConsoleStyle::clear();
    ConsoleStyle::header("Admin Login");

    ConsoleStyle::menu({
        "HEAD",
        "STAFF",
        "Back"
    });

    std::cout << "\nSelect role: ";
    int roleChoice;
    if (!(std::cin >> roleChoice)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        ConsoleStyle::setRed();
        std::cout << "Invalid input.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return;
    }

    AdminRole role;
    if (roleChoice == 1)
        role = AdminRole::HEAD;
    else if (roleChoice == 2)
        role = AdminRole::STAFF;
    else
        return;

    // ---- LOGIN ----
    bool loggedIn = false;
    std::string username;
    if (role == AdminRole::HEAD) {
        std::string password;
        std::cout << "Enter HEAD password: ";
        password = readPassword();
        loggedIn = AdminAuth::loginHead(password);
    } else {
        std::string password;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Username: ";
        std::getline(std::cin,username);
        std::cout << "Password: ";
        password = readPassword();
        loggedIn = AdminAuth::loginStaff(username, password);
    }

    if (!loggedIn) {
        ConsoleStyle::setRed();
        std::cout << "Login failed.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
        return;
    }else{
        ConsoleStyle::setGreen();
        std::cout<< "Login Successful.\n";
        ConsoleStyle::reset();
        ConsoleStyle::pause();
    }

    // ---- ROUTE TO MENU ----
    if (role == AdminRole::HEAD)
        headMenu(system);
    else
        staffMenu(system,username);
}

void AdminConsole::headMenu(BookingSystem& system) {
    while (true) {
        ConsoleStyle::clear();
        ConsoleStyle::header("HEAD ADMIN PANEL");

        ConsoleStyle::menu({
            "Station Management",
            "Train Management",
            "Coach Management",
            "Route Management",
            "Fare Management",
            "Staff Management",
            "Reports",
            "Back"
        });

        int choice;
        std::cout << "\nChoose option: ";
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
            case 1: AdminConsole::stationManagement(system); break;
            case 2: AdminConsole::trainManagement(system); break;
            case 3: AdminConsole::coachManagement(system); break;
            case 4: AdminConsole::routeManagement(system); break;
            case 5: AdminConsole::fareManagement(system); break;
            case 6: AdminConsole::staffManagement(system); break;
            case 7: AdminConsole::reportsMenu(system); break;
            case 8: return;
            default:
                ConsoleStyle::setRed();
                std::cout << "Invalid choice\n";
                ConsoleStyle::reset();
                ConsoleStyle::pause();
        }
    }
}


void AdminConsole::staffMenu(BookingSystem& system,const std::string& username) {
    while (true) {
        ConsoleStyle::clear();
        ConsoleStyle::header("STAFF ADMIN PANEL");

        ConsoleStyle::menu({
            "Station Management",
            "Train Management",
            "Coach Management",
            "Route Management",
            "Fare Management",
            "Reports",
            "My Profile",
            "Back"
        });

        int choice;
        std::cout << "\nChoose option: ";
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
            case 1: AdminConsole::stationManagement(system); break;
            case 2: AdminConsole::trainManagement(system); break;
            case 3: AdminConsole::coachManagement(system); break;
            case 4: AdminConsole::routeManagement(system); break;
            case 5: AdminConsole::fareManagement(system); break;
            case 6: AdminConsole::reportsMenu(system); break;
            case 7: AdminConsole::viewProfileFlow(username); break;
            case 8: return;
            default:
                ConsoleStyle::setRed();
                std::cout << "Invalid choice\n";
                ConsoleStyle::reset();
                ConsoleStyle::pause();
        }
    }
}

void AdminConsole::fareManagement(BookingSystem& system) {
    FareConfig& fc = system.getFareConfig();
    while (true) {
        ConsoleStyle::clear();
        ConsoleStyle::header("FARE MANAGEMENT");
        ConsoleStyle::menu({
            "View Fare Configuration",
            "Update GST",
            "Update Train Charge",
            "Update Coach Fare",
            "Update Discount",
            "Back"
        });
        int choice;
        std::cout << "\nChoose option: ";
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
        case 1: { //VIEW CONFIG
            ConsoleStyle::clear();
            ConsoleStyle::header("FARE CONFIGURATION");

            std::cout << "GST (%): " << fc.gstPercent << "\n";
            std::cout << "Discount (%): " << fc.discountPercent << "\n\n";

            std::cout << "Coach Fare (per km):\n";
            for (const auto& [coach, rate] : fc.coachRatePerKm) {
                std::cout << "  " << coach << " : " << rate << "\n";
            }

            std::cout << "\nTrain Charges:\n";
            for (const auto& [trainNo, charge] : fc.trainCharge) {
                std::cout << "  Train " << trainNo << " : " << charge << "\n";
            }

            ConsoleStyle::pause();
            break;
        }
        case 2: { //UPDATE GST
            ConsoleStyle::clear();
            ConsoleStyle::header("UPDATE GST");

            std::cout << "Enter new GST percentage: ";
            std::cin >> fc.gstPercent;

            system.saveFareConfig();
            ConsoleStyle::setGreen();
            std::cout << "GST updated successfully.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            break;
        }
        case 3: { //UPDATE TRAIN CHARGE
            ConsoleStyle::clear();
            ConsoleStyle::header("UPDATE TRAIN CHARGE");

            int trainNo;
            double charge;

            std::cout << "\nTrain Charges:\n";
            for (const auto& [trainNo, charge] : fc.trainCharge) {
                std::cout << "  Train " << trainNo << " : " << charge << "\n";
            }

            std::cout << "\nEnter Train Number: ";
            std::cin >> trainNo;
            std::cout << "Enter new charge: ";
            std::cin >> charge;

            fc.trainCharge[trainNo] = charge;
            system.saveFareConfig();

            ConsoleStyle::setGreen();
            std::cout << "Train charge updated successfully.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            break;
        }
        case 4: { //UPDATE COACH FARE
            ConsoleStyle::clear();
            ConsoleStyle::header("UPDATE COACH FARE");

            std::string coach;
            double rate;

            std::cout << "Coach Fare (per km):\n";
            for (const auto& [coach, rate] : fc.coachRatePerKm) {
                std::cout << "  " << coach << " : " << rate << "\n";
            }

            std::cout << "Enter coach type (GEN / SL / AC3 / AC2): ";
            std::cin >> coach;
            std::cout << "Enter fare per km: ";
            std::cin >> rate;

            fc.coachRatePerKm[coach] = rate;
            system.saveFareConfig();

            ConsoleStyle::setGreen();
            std::cout << "Coach fare updated successfully.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            break;
        }
        case 5: { //UPDATE DISCOUNT
            ConsoleStyle::clear();
            ConsoleStyle::header("UPDATE DISCOUNT");

            std::cout << "Enter discount percentage (0 for none): ";
            std::cin >> fc.discountPercent;

            system.saveFareConfig();
            ConsoleStyle::setGreen();
            std::cout << "Discount updated successfully.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            break;
        }
        case 6: return;
        default:
            ConsoleStyle::setRed();
            std::cout << "Invalid choice\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
        }
    }
}

void AdminConsole::staffManagement(BookingSystem& system) {
    while (true) {
        ConsoleStyle::clear();
        ConsoleStyle::header("Staff Management");

        ConsoleStyle::menu({
            "Add New Staff",
            "View Staff List",
            "Reset Staff Password",
            "Remove Staff",
            "Back"
        });
        int choice;
        std::cout << "\nChoose option: ";
        if (!(std::cin >> choice)){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            ConsoleStyle::setRed();
            std::cout << "Invalid input.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            continue;
        }
        switch (choice) {
            case 1: addStaffFlow(); break;
            case 2: viewStaffListFlow(); break;
            case 3: resetStaffPasswordFlow(); break;
            case 4: removeStaffFlow(); break;
            case 5: return;
            default: ConsoleStyle::pause();
        }
    }
}

void AdminConsole::stationManagement(BookingSystem& system) {
    while(true){
        ConsoleStyle::clear();
        ConsoleStyle::header("STATION MANAGEMENT");

        ConsoleStyle::menu({
            "Add Station",
            "View Stations",
            "Rename Station",
            "Remove Station",
            "Back"
        });

        int choice;
        std::cout << "\nChoose option: ";
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            ConsoleStyle::setRed();
            std::cout << "Invalid input.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            continue;
        }
        switch (choice)
        {
        case 1:
            addStationFlow(system);
            break;
        case 2:
            viewStationsFlow(system);
            break;
        case 3:
            renameStationFlow(system);
            break;
        case 4:
            removeStationFlow(system);
            break;
        case 5:
            return;
        default:
            std::cout << "Invalid choice\n";
            ConsoleStyle::pause();
        }
    }
}

void AdminConsole::trainManagement(BookingSystem& system) {
    while(true){
        ConsoleStyle::clear();
        ConsoleStyle::header("TRAIN MANAGEMENT");
        ConsoleStyle::menu({
            "Add Train",
            "View Trains",
            "Remove Train",
            "Activate / Deactivate Train",
            "Back"
        });
        int choice;
        std::cout << "\nChoose option: ";
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            ConsoleStyle::setRed();
            std::cout << "Invalid input.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            continue;
        }
        switch (choice)
        {
        case 1:
            addTrainFlow(system);
            break;
        case 2:{
            std::string date;
            std::cout << "Enter Date to view (YYYY-MM-DD): ";
            std::cin >> date;
            viewTrainsFlow(system,date);
            break;
        }
        case 3:
            removeTrainFlow(system);
            break;
        case 4:
            toggleTrainStatusFlow(system);
            break;
        case 5:
            return;
        default:
            std::cout << "Invalid choice\n";
            ConsoleStyle::pause();
        }
    }
}

void AdminConsole::coachManagement(BookingSystem& system) {
    while(true){
        ConsoleStyle::clear();
        ConsoleStyle::header("COACH MANAGEMENT");

        ConsoleStyle::menu({
            "Add Coach to Train",
            "Remove Coach from Train",
            "Update Coach Seats",
            "View Train Coaches",
            "Back"
        });

        int choice;
        std::cout << "\nChoose option: ";
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            ConsoleStyle::setRed();
            std::cout << "Invalid input.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            continue;
        }

        switch (choice)
        {
        case 1:
            addCoachFlow(system);
            break;
        case 2:
            removeCoachFlow(system);
            break;
        case 3:
            updateCoachSeatsFlow(system);
            break;
        case 4:
            viewTrainCoachesFlow(system);
            break;
        case 5:
            return;
        default:
            std::cout << "Invalid choice\n";
            ConsoleStyle::pause();
        }
    }
}

void AdminConsole::routeManagement(BookingSystem& system) {
    while(true){
        ConsoleStyle::clear();
        ConsoleStyle::header("ROUTE MANAGEMENT");

        ConsoleStyle::menu({
            "Assign Route to Train",
            "Add Station to Route",
            "Remove Station from Route",
            "View Train Route",
            "Back"
        });
        int trainNo, stationId;
        int choice;
        std::cout << "\nChoose option: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            ConsoleStyle::setRed();
            std::cout << "Invalid input.\n";
            ConsoleStyle::reset();
            ConsoleStyle::pause();
            continue;
        }
        if (choice == 5) return;
        switch (choice) {
            case 1: {
                system.showAllStations();
                std::cout << "Train Number: ";
                std::cin >> trainNo;
                std::cout << "Enter station IDs(-1 to stop) and Distance from the start: ";
                std::vector<RouteStop> route;
                while (true) {
                    int dist;
                    std::cout<<"Station Id: ";
                    std::cin >> stationId;
                    std::cout<<"Distance from start: ";
                    std::cin >> dist;
                    if (stationId == -1) break;
                    route.push_back({stationId,dist});
                }
                system.assignRouteToTrain(trainNo, route);
                ConsoleStyle::pause();
                break;
            }
            case 2:{
                int dist;
                std::cout << "Train No: ";
                std::cin >> trainNo;
                std::cout << "Station ID: ";
                std::cin >> stationId;
                std::cout << "distance from start: ";
                std::cin >> dist;
                system.addStationToTrainRoute(trainNo, stationId , dist);
                ConsoleStyle::pause();
                break;
            }
            case 3:
                std::cout << "Train No & Station ID: ";
                std::cin >> trainNo >> stationId;
                system.removeStationFromTrainRoute(trainNo, stationId);
                ConsoleStyle::pause();
                break;
            case 4:
                std::cout << "Train Number: ";
                std::cin >> trainNo;
                system.displayTrainRoute(trainNo);
                ConsoleStyle::pause();
                break;
            default:
                std::cout << "Invalid choice\n";
                ConsoleStyle::pause();
        }
    }
}

void AdminConsole::reportsMenu(BookingSystem& system) {
    while(true){
        ConsoleStyle::clear();
        ConsoleStyle::header("REPORTS PANEL");
        ConsoleStyle::menu({
            "System Summary",
            "User Booking Report",
            "Train Detailed Report",
            "Back"
        });
        int choice;
        std::cout << "\nChoose option: ";
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
            case 1:
                system.showSystemSummary();
                ConsoleStyle::pause();
                break;
            case 2: {
                std::string phone;
                std::cout << "Enter Phone Number: ";
                std::cin >> phone;
                User* user = system.getUserByPhone(phone);
                if (!user) {
                    ConsoleStyle::setRed();
                    std::cout << "No user found with this phone number.\n";
                    ConsoleStyle::reset();
                    ConsoleStyle::pause();
                    break;
                }
                system.showUserBookingReport(user->getId());
                ConsoleStyle::pause();
                break;
            }
            case 3: {
                ConsoleStyle::mainheader("  Available Trains & Routes  ");
                system.displayAllTrainsWithRoutes();
                int trainNo;
                std::cout << "\nEnter Train Number: ";
                std::cin >> trainNo;
                std::string journeyDate;
                std::cout << "Enter Journey Date (YYYY-MM-DD): ";
                std::cin >> journeyDate;
                ConsoleStyle::clear();
                system.showTrainDetailedReport(trainNo,journeyDate);
                ConsoleStyle::pause();
                break;
            }
            case 4:
                return;
            default:
                ConsoleStyle::setRed();
                std::cout << "Invalid choice\n";
                ConsoleStyle::reset();
                ConsoleStyle::pause();
        }
    }
}
