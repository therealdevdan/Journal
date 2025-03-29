#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <iostream>

#ifdef _WIN32 
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

namespace Utils {
    void clearConsole();
    void timeSleepOneSec();
    void ignoreEnter();
}

#endif
