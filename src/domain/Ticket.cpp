#include "domain/Ticket.h"
#include <fstream>
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
int Ticket::getTicketId() const {
    return ticketId;
}

std::string Ticket::getPnr() const {
    return pnr;
}

int Ticket::getTrainNumber() const {
    return trainNumber;
}

std::string Ticket::getTrainName() const {
    return trainName;
}

std::string Ticket::getFromStation() const {
    return fromStation;
}

std::string Ticket::getToStation() const {
    return toStation;
}

std::string Ticket::getjourneyDate() const {
    return journeyDate;
}

std::string Ticket::getCoachId() const {
    return coachId;
}

int Ticket::getSeatNumber() const {
    return seatNumber;
}

bool Ticket::getIsWaiting() const {
    return isWaiting;
}

int Ticket::getUserId() const {
    return userId;
}

std::string Ticket::getPassengerName() const {
    return passengerName;
}

int Ticket::getPassengerAge() const {
    return passengerAge;
}

std::string Ticket::getPassengerGender() const {
    return passengerGender;
}

double Ticket::getTotalFare() const {
    return fareResult.totalFare;
}

const FareResult& Ticket::getFareResult() const {
    return fareResult;
}

/* ---------- CONSOLE DISPLAY ---------- */
void Ticket::displayTicket() const {
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
    file << "body{background:#f0f2f5;display:flex;justify-content:center;align-items:center;min-height:100vh;margin:0;font-family:'Segoe UI',Tahoma,sans-serif;}\n";
    
    // Background card using the Matterhorn image from your request
    file << ".ticket-container{width:850px;height:520px;position:relative;border-radius:20px;overflow:hidden;box-shadow:0 15px 35px rgba(0,0,0,0.2);"
         << "background:url('https://media.istockphoto.com/id/1829848226/photo/happy-tourist-woman-looking-out-the-window-enjoying-with-the-snow-matterhorn-mountain-while.jpg?s=612x612&w=0&k=20&c=kGmqZIqqSn2yDz1eAL5A5qUVRXbO_fwIQD_iLkqzxJo=') center/cover;}\n";

    // Left-aligned PNR/Train Header
    file << ".brand-header{background:linear-gradient(to bottom, rgba(0,98,204,0.9), transparent);padding:15px 25px;color:white;display:flex;justify-content:space-between;align-items:flex-start;}\n";
    file << ".train-title-group{display:flex;flex-direction:column;gap:2px;}\n";
    file << ".brand-header h2{margin:0;font-size:18px;letter-spacing:0.5px;display:flex;align-items:center;gap:8px;}\n";
    file << ".pnr-train-info{font-size:12px;opacity:0.95;font-weight:400;}\n";

    // Glassmorphism Message Bubble
    file << ".ticket-bubble{position:absolute;bottom:25px;left:25px;width:360px;background:rgba(0,0,0,0.75);backdrop-filter:blur(12px);"
         << "border:1px solid rgba(255,255,255,0.2);border-radius:20px;border-bottom-left-radius:2px;padding:22px;color:white;box-shadow:0 10px 30px rgba(0,0,0,0.4);}\n";
    
    file << ".passenger-header{display:flex;justify-content:space-between;align-items:center;margin-bottom:12px;}\n";
    file << ".passenger-name{font-size:19px;font-weight:bold;color:#4dabf7;}\n";
    file << ".status-badge{background:" << statusColor << ";color:white;padding:4px 12px;border-radius:20px;font-size:11px;font-weight:bold;box-shadow:0 0 15px rgba(40,167,69,0.6);}\n";

    // Coach and Seat Pill style
    file << ".info-grid{font-size:14px;line-height:1.8;margin-bottom:15px;}\n";
    file << ".seat-pill{background:#4dabf7;color:#000;padding:2px 12px;border-radius:15px;font-weight:bold;font-size:13px;margin-left:5px;}\n";

    // Fare Split Table (Aligned Properly)
    file << ".fare-table{width:100%;border-top:1px solid rgba(255,255,255,0.2);padding-top:12px;font-size:13px;border-collapse:collapse;}\n";
    file << ".fare-table td{padding:3px 0;color:#ccc;}\n";
    file << ".fare-table .amount{text-align:right;font-family:monospace;}\n";
    file << ".total-row td{padding-top:8px;color:white;font-weight:bold;font-size:16px;}\n";

    // Print Button with Hover Transition
    file << ".print-btn{background:#fff;color:#0062cc;border:none;padding:10px 22px;border-radius:30px;font-weight:bold;font-size:12px;cursor:pointer;"
         << "text-transform:uppercase;box-shadow:0 4px 15px rgba(0,0,0,0.2);transition:all 0.3s cubic-bezier(0.175,0.885,0.32,1.275);display:flex;align-items:center;gap:8px;}\n";
    file << ".print-btn:hover{background:#0062cc;color:#fff;transform:translateY(-3px);box-shadow:0 8px 25px rgba(0, 98, 204, 0.4);}\n";
    
    file << "@media print{.print-btn{display:none;}}\n";
    file << "</style></head><body>\n";

    file << "<div class='ticket-container'>\n";
    
    // Header with PNR/Train on left
    file << "<div class='brand-header'>\n";
    file << "<div class='train-title-group'>\n";
    file << "<h2><i class='fas fa-train'></i> " << trainName << "</h2>\n";
    file << "<div class='pnr-train-info'>PNR: " << pnr << " | Train: " << trainNumber << "</div>\n";
    file << "</div>\n";
    file << "<button class='print-btn' onclick='window.print()'><i class='fas fa-print'></i> Print Ticket</button>\n";
    file << "</div>\n";

    // Info Bubble
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

    // Fare Split Table including Discount
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