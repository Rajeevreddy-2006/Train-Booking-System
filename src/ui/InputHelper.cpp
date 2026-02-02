#include "ui/InputHelper.h"
#include <conio.h>   // _getch()
#include <iostream>

std::string readPassword() {
    std::string password;
    char ch;

    while (true) {
        ch = _getch(); //Read only char,does not print on screen
        if (ch == '\r') { //'\r' - Enter key
            std::cout << std::endl;
            break;
        }
        else if (ch == '\b') { //'\b' - Backspace key
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; //'\b'- moves left , ' ' -replace '*' ,'\b' -adjust cursor
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    return password;
}
