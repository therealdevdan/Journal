#include "utils/utils.hpp"
#include <cstdlib>

void Utils::clearConsole() {
    system(CLEAR_SCREEN);
}

void Utils::timeSleepOneSec() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Utils::ignoreEnter() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
