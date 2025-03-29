#include "user/user.hpp"
#include "utils/utils.hpp"
#include <iostream>

User::User(const std::string& log, const std::string& password) 
    : log(log), password(password) {}

User::~User() {}

void User::personalAccount() {
    Utils::clearConsole();
    std::cout << "---------------------\n";
    std::cout << "Your Account Details\n";
    std::cout << "---------------------\n";
    std::cout << "Username: " << log << "\n";
    std::cout << "Password: " << password << "\n\n";

    std::cout << "Do you want to change your details?\n\n";

    bool correctAnswer = false;

    while(!correctAnswer) {
        std::string op;
        std::cout << "(yes/no): ";
        std::cin >> op;

        if(op == "yes") {
            updateData();
            correctAnswer = true;
        }
        else if(op == "no") {
            std::cout << "\nExiting account...\n";
            Utils::timeSleepOneSec();
            Utils::clearConsole();
            correctAnswer = true;
        }
        else {
            std::cout << "\nInvalid command, please try again.\n";
            correctAnswer = false;
        }
    }
}

User* User::updateData() {
    Utils::clearConsole();
    std::string newlog;
    std::string newPassword;
    std::cout << "Enter new username: ";
    std::cin >> newlog;
    std::cout << "Enter new password: ";
    std::cin >> newPassword;

    if (newlog.size() < 5 || newPassword.size() < 5) {
        std::cout << "--- ERROR --- Username and password must contain at least 5 characters!\n";
        return this;
    }

    log = newlog;
    password = newPassword;

    std::cout << "\nData updated successfully!\n";
    Utils::timeSleepOneSec();
    Utils::clearConsole();

    return this;
}
