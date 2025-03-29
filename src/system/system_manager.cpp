#include "system/system_manager.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>

void SystemManager::registration(bool isAdmin) {
    Utils::clearConsole();
    std::string log;
    std::string password;

    std::cout << "\nFor registration rules, enter 'H'\n";
    std::cout << "To continue, enter any character\n";
    std::cout << "\n";
    std::cout << "Enter command: ";

    char help;
    std::cin >> help;
    Utils::ignoreEnter();

    if(help == 'h' || help == 'H') {
        Utils::clearConsole();
        std::cout << "\n--- REGISTRATION RULES ---\n\n";
        std::cout << "---> Username and password must be at least 5 characters <---\n";
        std::cout << "---> Username and password cannot contain spaces <---\n";
        std::cout << "---> Username must start with uppercase letter <---\n";
        std::cout << "---> Username must contain at least one digit <---\n";
        std::cout << "---> Password must contain at least one special character (@#$&) <---\n\n";
    }

    bool validSize = false;
    bool validFirstChar = false;
    bool hasDigit = false;
    bool noSpaces = false;

    while(!validSize || !validFirstChar || !hasDigit || !noSpaces) {
        std::cout << "\nEnter username: ";
        std::getline(std::cin, log);

        if(log.size() < 5) {
            std::cout << "ERROR --> Username must be at least 5 characters!\n";
            validSize = false;
        } 
        else {
            validSize = true;
        }

        if(!isFirstCharacterUppercase(log)) {
            std::cout << "ERROR --> Username must start with uppercase letter!\n";
            validFirstChar = false;
        } 
        else {
            validFirstChar = true;
        }

        if(!containsDigit(log)) {
            std::cout << "ERROR --> Username must contain at least one digit!\n";
            hasDigit = false;
        } 
        else {
            hasDigit = true;
        }

        if(log.find(' ') != std::string::npos) {
            std::cout << "ERROR --> Username cannot contain spaces!\n";
            noSpaces = false;
        } 
        else {
            noSpaces = true;
        }
    }

    bool p_validSize = false;
    bool p_validFirstChar = false;
    bool p_hasDigit = false;
    bool p_hasSpecialChar = false;

    while(!p_validSize || !p_validFirstChar || !p_hasDigit || !p_hasSpecialChar) {
        std::cout << "\nEnter password: ";
        std::getline(std::cin, password);

        if(password.size() < 5) {
            std::cout << "ERROR --> Password must be at least 5 characters!\n";
            p_validSize = false;
        } 
        else {
            p_validSize = true;
        }

        if(!isFirstCharacterUppercase(password)) {
            std::cout << "ERROR --> Password must start with uppercase letter!\n";
            p_validFirstChar = false;
        } 
        else {
            p_validFirstChar = true;
        }

        if(!containsDigit(password)) {
            std::cout << "ERROR --> Password must contain at least one digit!\n";
            p_hasDigit = false;
        } 
        else {
            p_hasDigit = true;
        }

        if(!containsSpecialChar(password)) {
            std::cout << "ERROR --> Password must contain at least one special character (@#$&)!\n";
            p_hasSpecialChar = false;
        } 
        else {
            p_hasSpecialChar = true;
        }
    }

    if(isAdmin) {
        adminAccounts[log] = password; 
    } 
    else {
        studentAccounts[log] = std::make_pair(password, std::unordered_map<std::string, std::vector<std::string>>()); 
    }

    std::cout << "\nRegistration successful!\n\n";
    Utils::timeSleepOneSec();
    Utils::clearConsole();
}

User* SystemManager::login(bool isAdmin) {
    Utils::clearConsole();
    std::string log;
    std::string password;

    int attempts = 10;
    while(attempts > 0) {
        std::cout << "\nEnter username: ";
        std::cin >> log;

        std::cout << "Enter password: ";
        std::cin >> password;

        if(isAdmin) {
            auto it = adminAccounts.find(log);
            if(it != adminAccounts.end() && it->second == password) {
                std::cout << "Login successful!\n";
                return new Admin(log, password, studentAccounts, reviews, 
                               homeworks, adminMessages, grades); 
            }
        } 
        else {
            auto it = studentAccounts.find(log);
            if(it != studentAccounts.end() && it->second.first == password) {
                std::cout << "Login successful!\n";
                return new Student(log, password, studentAccounts, reviews, 
                                 homeworks, adminMessages, grades); 
            }
        }

        attempts--;
        std::cout << "\nInvalid username or password. Attempts remaining: " << attempts << "\n";
        Utils::timeSleepOneSec();
        Utils::clearConsole();
    }

    std::cout << "Too many failed attempts.\n";
    return nullptr;
}

bool SystemManager::containsDigit(const std::string& str) {
    return std::any_of(str.begin(), str.end(), [](char ch) {
        return std::isdigit(ch);
    });
}

bool SystemManager::containsSpecialChar(const std::string& str) {
    return std::any_of(str.begin(), str.end(), [](char ch) {
        return std::ispunct(ch);
    });
}

bool SystemManager::isFirstCharacterUppercase(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    return std::isupper(static_cast<unsigned char>(str[0]));
}
