#include "user/student.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <ctime>

Student::Student(const std::string& log, const std::string& password, 
                unor_map_vec& studentData,
                std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& reviews,
                std::unordered_map<std::string, std::string>& homework,
                std::unordered_map<std::string, std::pair<std::string, std::string>>& messages,
                std::unordered_map<std::string, std::vector<Grade>>& grades)
    : User(log, password), 
      studentData(studentData),
      adminMessages(messages),
      homeworks(homework),
      reviews(reviews),
      grades(grades) {}

void Student::showMenu() {
    Utils::clearConsole();
    bool inMenu = true;

    while(inMenu) {
        std::cout << "--------------------------Student Menu--------------------------\n";
        std::cout << "\n";
        std::cout << "1. View schedule\n";
        std::cout << "2. View homework\n";
        std::cout << "3. View grades\n";
        std::cout << "4. View study materials\n";
        std::cout << "5. View reviews\n";
        std::cout << "6. Personal account\n";
        std::cout << "7. Message administration\n";
        std::cout << "8. Return to role selection\n";

        std::cout << "\nEnter option: ";
        int action;

        std::cin >> action;
        Utils::ignoreEnter();

        switch(action) {
            case 1:
                viewSchedule();
                break;
            case 2:
                viewHomework();
                break;
            case 3:
                viewGrades();
                break;
            case 4:
                viewStudyMaterials();
                break;
            case 5:
                viewReviews();
                break;
            case 6:
                personalAccount();
                break;
            case 7:
                sendMessageToAdmin();
                break;
            case 8:
                inMenu = false;
                Utils::clearConsole();
                break;
            default:
                invalidCommand();
                break;
        }
    }
}

void Student::invalidCommand() {
    std::cout << "\nInvalid command, please try again later...\n";
}

void Student::viewHomework() {
    Utils::clearConsole();
    std::cout << "Your homework assignments:\n\n";

    for(const auto &[subject, assignment] : homeworks) {
        std::cout << "Subject: " << subject << "\n";
        std::cout << "- " << assignment << "\n\n";
    }
}

void Student::viewStudyMaterials() {
    Utils::clearConsole();
    std::cout << "\nNo materials available yet!\n\n";
}

void Student::viewGrades() {
    Utils::clearConsole();
    auto& myGrades = grades[this->log];
    if (myGrades.empty()) {
        std::cout << "No grades available yet.\n";
        return;
    }
    for (const auto& g : myGrades) {
        std::cout << "Subject: " << g.subject 
                 << " | Grade: " << g.grade 
                 << "\nComment: " << g.comment 
                 << "\nDate: " << std::ctime(&g.time) << "\n";
    }
}

void Student::viewReviews() {
    Utils::clearConsole();
    auto it = reviews.find(log);
    if (it != reviews.end() && !it->second.empty()) {
        std::cout << "Your reviews:\n";
        for (const auto& review : it->second) {
            std::cout << "From: " << review.first << "\n";
            std::cout << "Review: " << review.second << "\n\n";
        }
    }
    else {
        std::cout << "No reviews available yet.\n";
    }
}

void Student::sendMessageToAdmin() {
    Utils::clearConsole();

    std::string firstName;
    std::cout << "Enter your first name\n";
    std::cout << "- ";
    std::getline(std::cin, firstName);

    std::string lastName;
    std::cout << "Enter your last name\n";
    std::cout << "- ";
    std::getline(std::cin, lastName);

    std::cout << "\n";
    std::string message;
    std::cout << "Enter your message (be respectful)\n";
    std::cout << "Your message: ";
    std::getline(std::cin, message);

    adminMessages[firstName] = std::make_pair(lastName, message);
    std::cout << "\nSending message...\n";
    Utils::timeSleepOneSec();

    std::cout << "Message sent!\n\n"; 
    std::this_thread::sleep_for(std::chrono::seconds(2));
    Utils::clearConsole();              
}

void Student::viewSchedule() {
    auto it = studentData.find(log);
    if(it != studentData.end()) {
        for(auto &[day, lessons] : it->second.second) {
            std::cout << "--- Your schedule for " << day << " ---\n\n";
            for(const auto &lesson : lessons) {
                std::cout << " -" << lesson << "\n";
            }
        }
        return;
    }
    std::cout << "\nSchedule not found\n";
}
