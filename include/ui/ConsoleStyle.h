#pragma once
#include <string>
#include <vector>

class ConsoleStyle {
public:
    static void clear();
    static void banner();
    static void showEnd();
    static void mainheader(const std::string& title);
    static void header(const std::string& title);
    static void menu(const std::vector<std::string>& options);
    static void pause();

    // colors
    static void setGreen();
    static void setBlue();
    static void setRed();
    static void setYellow();
    static void reset();
};