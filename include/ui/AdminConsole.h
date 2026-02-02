#pragma once
#include "core/BookingSystem.h"

class AdminConsole {
public:
    static void run(BookingSystem& system);
    static void stationManagement(BookingSystem& system);
    static void trainManagement(BookingSystem& system);
    static void coachManagement(BookingSystem& system);
    static void routeManagement(BookingSystem& system);
    static void reportsMenu(BookingSystem& system);

    static void addStationFlow(BookingSystem& system);
    static void viewStationsFlow(BookingSystem& system);
    static void renameStationFlow(BookingSystem& system);
    static void removeStationFlow(BookingSystem& system);

    static void addTrainFlow(BookingSystem& system);
    static void viewTrainsFlow(BookingSystem& system,const std::string& date);
    static void removeTrainFlow(BookingSystem& system);
    static void toggleTrainStatusFlow(BookingSystem& system);

    static void addCoachFlow(BookingSystem& system);
    static void removeCoachFlow(BookingSystem& system);
    static void updateCoachSeatsFlow(BookingSystem& system);
    static void viewTrainCoachesFlow(BookingSystem& system);

    static void fareManagement(BookingSystem& system);
    static void viewFareFlow(BookingSystem& system);
    static void updateGstFlow(BookingSystem& system);
    static void updateTrainChargeFlow(BookingSystem& system);
    static void updateCoachFareFlow(BookingSystem& system);
    static void updateDiscountFlow(BookingSystem& system);

    static void staffManagement(BookingSystem& system);
    static void headMenu(BookingSystem& system);
    static void staffMenu(BookingSystem& system,const std::string& username);
    static void addStaffFlow();
    static void viewStaffListFlow();
    static void resetStaffPasswordFlow();
    static void removeStaffFlow();
    static void viewProfileFlow(const std::string& staffName);
};
