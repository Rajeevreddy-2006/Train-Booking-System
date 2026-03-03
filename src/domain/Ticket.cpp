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
    std::cout << "Train        : " << trainName << " (" << trainNumber << ")\n";
    std::cout << "Route        : " << fromStation << " -> " << toStation << "\n";
    std::cout << "Coach        : " << coachId << "\n";

    if (isWaiting) std::cout << "Status       : WAITING LIST\n";
    else std::cout << "Seat No      : " << seatNumber << "\n";

    std::cout << "Journey Date : " << journeyDate << "\n";
    std::cout << "Passenger    : " << passengerName
              << " (" << passengerAge
              << ", " << passengerGender << ")\n";

    std::cout << "\nTotal Fare   : ₹" << fareResult.totalFare << "\n";
    std::cout << "Fare Split:\n";

    std::cout << "  Base Fare        : +₹" << fareResult.baseFare << "\n";

    if (fareResult.superfastCharge > 0)
        std::cout << "  Superfast Charge : +₹" << fareResult.superfastCharge << "\n";

    if (fareResult.reservationCharge > 0)
        std::cout << "  Reservation      : +₹" << fareResult.reservationCharge << "\n";

    if (fareResult.tatkalCharge > 0)
        std::cout << "  Tatkal Charge    : +₹" << fareResult.tatkalCharge << "\n";

    std::cout << "  GST              : +₹" << fareResult.gst << "\n";

    if (fareResult.discount > 0)
        std::cout << "  Discount         : -₹" << fareResult.discount << "\n";

    std::cout << "----------------------------------\n";
}

void Ticket::generateHTML(const std::string& filename,const std::string& userName) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    std::string statusText  = isWaiting ? "WAITING" : "CONFIRMED";
    std::string statusColor = isWaiting ? "#f59e0b" : "#28a745";

    file << "<!DOCTYPE html><html><head><meta charset='UTF-8'>\n";
    file << "<title>Ticket - " << passengerName << "</title>\n";
    file << "<link href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css' rel='stylesheet'>\n";

    file << "<style>\n";

    file << "body{margin:0;font-family:'Segoe UI',sans-serif;"
         << "background:#f0f2f5;display:flex;"
         << "justify-content:center;align-items:center;"
         << "min-height:100vh;}\n";

    /* PRINT SAFE */
    file << "@media print {"
     << "body{margin:0;background:white !important;"
     << "-webkit-print-color-adjust:exact !important;"
     << "print-color-adjust:exact !important;}"
     << ".print-btn{display:none !important;}"
     << ".ticket-outer{box-shadow:none !important;width:100% !important;}"
     << ".ticket-inner{background:#0f172a !important;color:white !important;}"
     << "}\n";

    /* Outer Container */
    file << ".ticket-outer{width:880px;"
         << "border-radius:22px;"
         << "background:linear-gradient(to bottom,"
         << "rgba(0,80,200,0.85) 0%,"
         << "rgba(0,40,100,0.25) 20%,"
         << "transparent 40%),"
         << "url('Images/ticket_background.jpg') center/cover no-repeat;"
         << "box-shadow:0 15px 40px rgba(0,0,0,0.35);"
         << "display:flex;flex-direction:column;"
         << "padding-bottom:40px;"
         << "-webkit-print-color-adjust:exact;}\n";

    file << ".header{display:flex;justify-content:space-between;"
         << "align-items:center;padding:18px 28px;}\n";

    file << ".train-info{color:white;font-size:22px;"
         << "font-weight:bold;text-shadow:0 2px 4px rgba(0,0,0,0.4);}\n";

    file << ".print-btn{background:white;color:#0a1931;"
         << "border:none;padding:6px 16px;border-radius:10px;"
         << "font-weight:bold;font-size:12px;cursor:pointer;}\n";

    /* Bubble */
    file << ".ticket-inner{width:360px;margin-left:50px;"
     << "margin-top:30px;"
     << "background:#0f172a;"   /* solid dark background */
     << "border-radius:18px;padding:22px;"
     << "border:1px solid rgba(255,255,255,0.15);"
     << "color:white;"
     << "-webkit-print-color-adjust:exact;"
     << "print-color-adjust:exact;}\n";

    file << ".passenger-name{font-size:18px;font-weight:bold;"
         << "color:#4dabf7;}\n";

    file << ".status{background:" << statusColor
         << ";color:white;padding:3px 10px;"
         << "border-radius:16px;font-size:9px;font-weight:bold;}\n";

    file << ".grid{display:grid;grid-template-columns:1fr 1fr;"
         << "gap:10px;border-top:1px solid rgba(255,255,255,0.1);"
         << "padding-top:10px;margin-top:10px;}\n";

    file << ".label{color:#94a3b8;font-size:8px;text-transform:uppercase;}\n";
    file << ".val{font-size:13px;font-weight:bold;color:white;}\n";

    file << ".fare-table{width:100%;margin-top:15px;"
         << "border-top:1px solid rgba(255,255,255,0.15);"
         << "padding-top:8px;border-collapse:collapse;}\n";

    file << ".fare-table td{padding:3px 0;font-size:12px;color:#cbd5e1;}\n";
    file << ".amt{text-align:right;font-weight:bold;color:white;}\n";

    file << ".total-row td{padding-top:8px;font-size:15px;"
         << "font-weight:800;color:white;"
         << "border-top:1px solid rgba(255,255,255,0.2);}\n";

    file << ".footer{display:flex;justify-content:space-between;"
         << "margin-top:12px;padding-top:8px;"
         << "border-top:1px dashed rgba(255,255,255,0.2);"
         << "font-size:9px;color:rgba(255,255,255,0.6);}\n";

    file << "</style></head><body>\n";

    file << "<div class='ticket-outer'>\n";

    file << "<div class='header'>\n";
    file << "<div class='train-info'><i class='fas fa-train'></i> "
         << trainName << " <span style='font-size:11px;opacity:0.7;'>@ "
         << trainNumber << "</span></div>\n";
    file << "<button class='print-btn' onclick='window.print()'>"
         << "<i class='fas fa-print'></i> PRINT</button>\n";
    file << "</div>\n";

    file << "<div class='ticket-inner'>\n";

    file << "<div style='display:flex;justify-content:space-between;align-items:center;'>\n";
    file << "<span class='passenger-name'>" << passengerName
         << " (" << passengerAge << ", "
         << passengerGender << ")</span>\n";
    file << "<span class='status'>" << statusText << "</span>\n";
    file << "</div>\n";

    file << "<div class='grid'>\n";
    file << "<div><div class='label'>From Station</div><div class='val'>"
         << fromStation << "</div></div>\n";
    file << "<div><div class='label'>To Station</div><div class='val'>"
         << toStation << "</div></div>\n";
    file << "<div><div class='label'>Date of Journey</div><div class='val'>"
         << journeyDate << "</div></div>\n";
    file << "<div><div class='label'>Coach / Seat</div><div class='val' "
         << "style='color:#4dabf7'>" << coachId
         << " / " << seatNumber << "</div></div>\n";
    file << "</div>\n";

    file << "<table class='fare-table'>\n";
    file << "<tr><td>Base Fare</td><td class='amt'>&#8377;"
         << fareResult.baseFare << "</td></tr>\n";

    if (fareResult.superfastCharge > 0)
        file << "<tr><td>Superfast</td><td class='amt'>&#8377;"
             << fareResult.superfastCharge << "</td></tr>\n";

    if (fareResult.reservationCharge > 0)
        file << "<tr><td>Reservation</td><td class='amt'>&#8377;"
             << fareResult.reservationCharge << "</td></tr>\n";

    if (fareResult.tatkalCharge > 0)
        file << "<tr><td>Tatkal</td><td class='amt'>&#8377;"
             << fareResult.tatkalCharge << "</td></tr>\n";

    file << "<tr><td>GST</td><td class='amt'>&#8377;"
         << fareResult.gst << "</td></tr>\n";

    file << "<tr class='total-row'><td>Total Paid</td>"
         << "<td class='amt'>&#8377;" << fareResult.totalFare
         << "</td></tr>\n";

    file << "</table>\n";

    file << "<div class='footer'>\n";
    file << "<span>PNR: " << pnr << "</span>\n";
    file << "<span>Booked by: " << userName << "</span>\n";
    file << "</div>\n";

    file << "</div></div></body></html>";

    file.close();
}