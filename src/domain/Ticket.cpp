#include "domain/Ticket.h"
#include <fstream>
#include <string>
#include <iostream>

Ticket::Ticket(int ticketId,const std::string& pnr,int trainNumber,const std::string& trainName,const std::string& coachId,
    int seatNumber,int userId,const std::string& journeyDate,const std::string& fromStation,const std::string& toStation,
    const std::string& passengerName,int passengerAge,const std::string& passengerGender,const FareResult& fareResult,
    bool isWaiting 
)
    : ticketId(ticketId),pnr(pnr),trainNumber(trainNumber),trainName(trainName),coachId(coachId),seatNumber(seatNumber),
      userId(userId),journeyDate(journeyDate),fromStation(fromStation),toStation(toStation),passengerName(passengerName),
      passengerAge(passengerAge),passengerGender(passengerGender),fareResult(fareResult),isWaiting(isWaiting) { }

//GETTERS
int Ticket::getTicketId() {
    return ticketId;
}

std::string Ticket::getPnr() {
    return pnr;
}

int Ticket::getTrainNumber() {
    return trainNumber;
}

std::string Ticket::getTrainName() {
    return trainName;
}

std::string Ticket::getFromStation() {
    return fromStation;
}

std::string Ticket::getToStation() {
    return toStation;
}

std::string Ticket::getjourneyDate() {
    return journeyDate;
}

std::string Ticket::getCoachId() {
    return coachId;
}

int Ticket::getSeatNumber() {
    return seatNumber;
}

bool Ticket::getIsWaiting() {
    return isWaiting;
}

int Ticket::getUserId() {
    return userId;
}

std::string Ticket::getPassengerName() {
    return passengerName;
}

int Ticket::getPassengerAge() {
    return passengerAge;
}

std::string Ticket::getPassengerGender() {
    return passengerGender;
}

double Ticket::getTotalFare() {
    return fareResult.totalFare;
}

FareResult& Ticket::getFareResult() {
    return fareResult;
}

/* ---------- CONSOLE DISPLAY ---------- */
void Ticket::displayTicket() {
    std::cout << "----------------------------------\n";
    std::cout << "PNR          : " << pnr << "\n";
    std::cout << "Train        : " << trainName
              << " (" << trainNumber << ")\n";
    std::cout << "Route        : " << fromStation
              << " -> " << toStation << "\n";
    std::cout << "Coach        : " << coachId << "\n";

    if (isWaiting)
        std::cout << "Status       : WAITING LIST\n";
    else
        std::cout << "Seat No      : " << seatNumber << "\n";

    std::cout << "Journey Date : " << journeyDate << "\n";
    std::cout << "Passenger    : " << passengerName
              << " (" << passengerAge
              << ", " << passengerGender << ")\n";

    std::cout << "\nTotal Fare   : ₹" << fareResult.totalFare << "\n";
    std::cout << "Fare Split:\n";
    std::cout << "  Base Fare    : +₹" << fareResult.baseFare << "\n";
    std::cout << "  Train Charge : +₹" << fareResult.trainCharge << "\n";
    std::cout << "  Discount     : -₹" << fareResult.discountAmount << "\n";
    std::cout << "  GST          : +₹" << fareResult.gstAmount << "\n";
    std::cout << "----------------------------------\n";
}

void Ticket::generateHTML(const std::string& filename, const std::string& userName) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    // Dynamic status based on booking state
    std::string statusText = isWaiting ? "WAITING" : "CONFIRMED";
    std::string statusColor = isWaiting ? "#f59e0b" : "#28a745";

    file << "<!DOCTYPE html><html><head><meta charset='UTF-8'>\n";
    file << "<title>Journey Ticket - " << trainName << "</title>\n";
    file << "<link href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css' rel='stylesheet'>\n";

    file << "<style>\n";
    // Base Styles
    file << "body{background:#f0f2f5;display:flex;justify-content:center;align-items:center;min-height:100vh;margin:0;font-family:'Segoe UI',Tahoma,sans-serif;}\n";
    
    // FORCING PRINT COLORS - This is the fix for "everything gone"
    file << "@media print {\n";
    file << "  body { -webkit-print-color-adjust: exact !important; print-color-adjust: exact !important; background: #f0f2f5 !important; }\n";
    file << "  .print-btn { display: none !important; }\n"; // Hides print button on paper
    file << "  .ticket-container { box-shadow: none !important; border: 1px solid #ccc; }\n";
    file << "}\n";

    file << ".ticket-container{width:850px;height:520px;position:relative;border-radius:20px;overflow:hidden;box-shadow:0 15px 35px rgba(0,0,0,0.2);"
         << "background:url('Images/ticket_background.jpg') center/cover no-repeat; -webkit-print-color-adjust: exact;}\n";

    file << ".brand-header{background:linear-gradient(to bottom, rgba(0,98,204,0.9), transparent);padding:15px 25px;color:white !important;display:flex;justify-content:space-between;align-items:flex-start; -webkit-print-color-adjust: exact;}\n";
    file << ".train-title-group{display:flex;flex-direction:column;gap:2px;}\n";
    file << ".brand-header h2{margin:0;font-size:18px;letter-spacing:0.5px;display:flex;align-items:center;gap:8px;color:white !important;}\n";
    file << ".pnr-train-info{font-size:12px;opacity:0.95;font-weight:400;color:white !important;}\n";

    // Enhanced the background alpha for better print visibility
    file << ".ticket-bubble{position:absolute;bottom:25px;left:25px;width:360px;background:rgba(0,0,0,0.85) !important;backdrop-filter:blur(12px);"
         << "border:1px solid rgba(255,255,255,0.2);border-radius:20px;border-bottom-left-radius:2px;padding:22px;color:white !important;"
         << "box-shadow:0 10px 30px rgba(0,0,0,0.4); -webkit-print-color-adjust: exact;}\n";
    
    file << ".passenger-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:12px;}\n";
    file << ".passenger-name{font-size:19px;font-weight:bold;color:#4dabf7 !important; -webkit-print-color-adjust: exact;}\n";
    file << ".status-badge{background:" << statusColor << " !important;color:white !important;padding:4px 12px;border-radius:20px;font-size:11px;font-weight:bold; -webkit-print-color-adjust: exact;}\n";

    file << ".info-grid{font-size:14px;line-height:1.8;margin-bottom:15px;color:white !important;}\n";
    file << ".seat-pill{background:#4dabf7 !important;color:#000 !important;padding:2px 12px;border-radius:15px;font-weight:bold;font-size:13px;margin-left:5px; -webkit-print-color-adjust: exact;}\n";

    file << ".fare-table{width:100%;border-top:1px solid rgba(255,255,255,0.2);padding-top:12px;font-size:13px;border-collapse:collapse;}\n";
    file << ".fare-table td{padding:3px 0;color:#ccc !important;}\n";
    file << ".fare-table .amount{text-align:right;font-family:monospace;color:white !important;}\n";
    file << ".total-row td{padding-top:8px;color:white !important;font-weight:bold;font-size:16px;}\n";

    file << ".print-btn{background:#fff;color:#0062cc;border:none;padding:10px 22px;border-radius:30px;font-weight:bold;font-size:12px;cursor:pointer;"
         << "text-transform:uppercase;box-shadow:0 4px 15px rgba(0,0,0,0.2);transition:all 0.3s ease;display:flex;align-items:center;gap:8px;}\n";
    file << ".print-btn:hover{background:#0062cc;color:#fff;}\n";
    
    file << "</style></head><body>\n";

    file << "<div class='ticket-container'>\n";
    
    // Header section
    file << "<div class='brand-header'>\n";
    file << "<div class='train-title-group'>\n";
    file << "<h2><i class='fas fa-train'></i> " << trainName << "</h2>\n";
    file << "<div class='pnr-train-info'>PNR: " << pnr << " | Train: " << trainNumber << "</div>\n";
    file << "</div>\n";
    file << "<button class='print-btn' onclick='window.print()'><i class='fas fa-print'></i> Print Ticket</button>\n";
    file << "</div>\n";

    // Passenger Info Bubble
    file << "<div class='ticket-bubble'>\n";
    file << "<div class='passenger-header'>\n";
    file << "<span class='passenger-name'>" << passengerName << " (" << passengerAge << ", " << passengerGender << ")</span>\n";
    file << "<span class='status-badge'>" << statusText << "</span>\n";
    file << "</div>\n";

    file << "<div class='info-grid'>\n";
    file << "<div><strong>From:</strong> " << fromStation << "</div>\n";
    file << "<div><strong>To:</strong> " << toStation << "</div>\n";
    file << "<div><strong>Date:</strong> " << journeyDate << "</div>\n";
    file << "<div><strong>Coach:</strong> " << coachId << " <span class='seat-pill'>Seat " << seatNumber << "</span></div>\n";
    file << "<div style='font-size:11px;color:#aaa;margin-top:4px;'>Booked by: " << userName << "</div>\n";
    file << "</div>\n";

    // Fare breakdown table
    file << "<table class='fare-table'>\n";
    file << "<tr><td>Base Fare</td><td class='amount'>₹" << fareResult.baseFare << "</td></tr>\n";
    file << "<tr><td>Train Charge</td><td class='amount'>₹" << fareResult.trainCharge << "</td></tr>\n";
    file << "<tr><td>Discount</td><td class='amount'>-₹" << fareResult.discountAmount << "</td></tr>\n";
    file << "<tr><td>GST</td><td class='amount'>₹" << fareResult.gstAmount << "</td></tr>\n";
    file << "<tr class='total-row'><td>Total Amount</td><td class='amount'>₹" << fareResult.totalFare << "</td></tr>\n";
    file << "</table>\n";

    file << "</div></div></body></html>";
    file.close();
}