#include "ui/ConsoleStyle.h"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <limits>

void ConsoleStyle::clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// void ConsoleStyle::banner() {
//     std::cout << R"(
// ================================================================


//  ██████╗  █████╗ ██╗██╗     ███╗   ██╗███████╗███████╗████████╗
//  ██╔══██╗██╔══██╗██║██║     ████╗  ██║██╔════╝██╔════╝╚══██╔══╝
//  ██████╔╝███████║██║██║     ██╔██╗ ██║█████╗  ███████╗   ██║   
//  ██╔══██╗██╔══██║██║██║     ██║╚██╗██║██╔══╝  ╚════██║   ██║   
//  ██║  ██║██║  ██║██║███████╗██║ ╚████║███████╗███████║   ██║   
//  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═══╝╚══════╝╚══════╝   ╚═╝   

//         RailNest - Train Management & Reservation System
//               Simple • Secure • Scalable • Console App

//  ================================================================

// )";
// }

void ConsoleStyle::banner() {
    std::string banner =
R"ASCII(
*================================================================================================*
                            ______      _ _   _   _           _   
                            | ___ \    (_) | | \ | |         | |  
                            | |_/ /__ _ _| | |  \| | ___  ___| |_ 
                            |    // _` | | | | . ` |/ _ \/ __| __|     
                            | |\ \ (_| | | | | |\  |  __/\__ \ |_ 
                            \_| \_\__,_|_|_| \_| \_/\___||___/\__|
                            Train Management & Reservation System
                            Simple • Secure • Scalable • Console App

                                 🚆 Welcome to RailNest 🚆
*================================@@======================@@=====================================*                                                                                                                  
)ASCII";
    std::cout << banner;
}

void ConsoleStyle::showEnd() {
    std::cout << R"(

                                          &&&&&&&&&
                                        &&&
                                       &&
                                      &  _____ ___________
                                     II__|[] | |   I I   |
                                    |        |_|_  I I  _|
                                   < OO----OOO   OO---OO
**********************************************************

"✨Signing off… Have a Safe and pleasant Journey!"
)";
}

void ConsoleStyle::mainheader(const std::string& title) {
    setSageGreen();
    std::cout << "\n=========================================\n";
    std::cout << " " << title << "\n";
    std::cout << "=========================================\n";
    reset();
}

void ConsoleStyle::header(const std::string& title) {
    setCyan();
    std::cout << "\n=====================\n";
    std::cout << "  " << title << "\n";
    std::cout << "=====================\n";
    reset();
}

void ConsoleStyle::menu(const std::vector<std::string>& options) {
    setYellow();
    std::cout << "┌──────┬──────────────────────────────┐\n";
    std::cout << "│ No   │ Option                       │\n";
    std::cout << "├──────┼──────────────────────────────┤\n";

    for (int i = 0; i < options.size(); ++i) {
        std::cout << "│ ";
        std::cout.width(4);
        std::cout << std::left << i + 1 << " │ ";
        std::cout.width(28);
        std::cout << std::left << options[i] << " │\n";
    }

    std::cout << "└──────┴──────────────────────────────┘\n";
    reset();
}

void ConsoleStyle::pause() {
    std::cout << "\nPress ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleStyle::setGreen() { std::cout << "\033[1;32m"; } //ANSI escape code
void ConsoleStyle::setBlue()  { std::cout << "\033[1;34m"; }
void ConsoleStyle::setRed()   { std::cout << "\033[1;31m"; }
void ConsoleStyle::setYellow() { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); }
void ConsoleStyle::setCyan() { std::cout << "\033[36m"; }
void ConsoleStyle::setMagenta() { std::cout << "\033[35m"; }
void ConsoleStyle::setBrightVoilet() { std::cout << "\033[95m"; }
void ConsoleStyle::setSageGreen() { std::cout << "\033[38;2;156;175;136m"; }
void ConsoleStyle::reset()    { std::cout << "\033[0m"; }