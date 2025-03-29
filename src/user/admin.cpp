#include "user/admin.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <ctime>

Admin::Admin(const std::string& log, const std::string& password, 
             unor_map_vec& studentData,
             std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& reviews,
             std::unordered_map<std::string, std::string>& homework,
             std::unordered_map<std::string, std::pair<std::string, std::string>>& messages,
             std::unordered_map<std::string, std::vector<Grade>>& grades)
    : User(log, password), studentData(studentData), reviews(reviews),
      homeworks(homework), adminMessages(messages), grades(grades) {}

void Admin::showMenu() {
    Utils::clearConsole();

    bool inMenu = true;
    while(inMenu) {
        std::cout << "\n";
        std::cout << "--------------------------Admin Menu--------------------------\n";
        std::cout << "\n";
        std::cout << "1. Edit student schedule\n";
        std::cout << "2. Write student review\n";
        std::cout << "3. Create homework assignment\n";
        std::cout << "4. Add grade\n";
        std::cout << "5. Personal account\n";
        std::cout << "6. Show all students\n";
        std::cout << "7. View messages\n";
        std::cout << "8. Return to role selection\n";

        std::cout << "\nEnter option: ";
        int action;

        std::cin >> action;
        Utils::ignoreEnter();

        switch(action) {
            case 1:
                editStudentSchedule();
                break;
            case 2:
                writeStudentReview();
                break;
            case 3:
                createHomework();
                break;
            case 4:
                addStudentGrade();
                break;
            case 5:
                personalAccount();
                break;
            case 6:
                listAllStudents();
                break;
            case 7:
                viewMessages();
                break;
            case 8:
                inMenu = false;
                Utils::clearConsole();
                break;
            default:
                std::cout << "Invalid command!\n";
                break;
        }
    }
}

void Admin::addStudentGrade() {
    Utils::clearConsole();
    bool validLog = false;
    std::string studentLog;

    while(!validLog) {
        std::cout << "Enter student username: ";
        std::getline(std::cin, studentLog);

        if(studentData.find(studentLog) != studentData.end()) {
            validLog = true;
        } 
        else {
            std::cout << "\nInvalid username, try again? (yes/no)\n";
            std::cout << "- ";
            std::string cont;
            std::getline(std::cin, cont);

            if(cont != "yes") {
                std::cout << "Canceling operation...\n";
                return;
            }
        }
    }

    std::string subject;
    std::cout << "Enter subject: ";
    std::getline(std::cin, subject);

    int grade;
    std::cout << "Enter grade (1-5): ";
    std::cin >> grade;
    Utils::ignoreEnter();

    std::string comment;
    std::string op;
    std::cout << "\nAdd comment? (yes/no): ";
    std::getline(std::cin, op);

    if(op == "yes") {
        std::cout << "Enter comment: ";
        std::getline(std::cin, comment);
    } else {
        comment = "No comment";
    }

    Grade g{subject, grade, comment, std::time(nullptr)};
    grades[studentLog].push_back(g);
    std::cout << "\n";

    Utils::timeSleepOneSec();
    Utils::clearConsole();
    std::cout << "Grade added successfully!\n";
}

void Admin::viewMessages() {
    Utils::clearConsole();

    std::cout << "Your messages:\n";

    for(const auto& [firstName, lastNameAndMessage] : adminMessages) {
        std::cout << "\n";
        std::cout << "*You have 1 message from student\n";
        std::cout << "\n";
        std::cout << "First name: " << firstName << "\n";
        std::cout << "Last name: " << lastNameAndMessage.first << "\n\n";
        std::cout << "Message:\n- " << lastNameAndMessage.second << "\n";
    }
    std::cout << "\n";
}

void Admin::listAllStudents() {
    Utils::clearConsole();
    std::cout << "Student list:\n\n";

    int studentCount = 1;
    for(const auto &[log, data] : studentData) {
        std::cout << "Student " << studentCount << " username: " << log << "\n";
        studentCount++;
    }
}

void Admin::editStudentSchedule() {
    std::string studentLog;
    bool validLog = false;
    std::cout << "Enter the username of the student whose schedule you want to edit\n";
    while(!validLog) {
        std::cout << "\nEnter username: ";
        std::getline(std::cin, studentLog);
        std::cout << "\n";

        auto it = studentData.find(studentLog);
        if(it != studentData.end()) {
            validLog = true;
        }
        else {
            std::cout << "Username not found. Please try again.\n";
        }
    }

    std::cout << "\nEnter weekdays to add/edit schedule. Type 'end' to finish.\n\n";

    std::unordered_map<std::string, std::vector<std::string>> schedule;

    while(true) {
        std::string day;
        std::cout << "Weekday: ";
        std::getline(std::cin, day);
        std::cout << "\n";
        if(day == "end") {
            break;
        }

        std::vector<std::string> lessons;
        while(true) {
            std::string lesson;
            std::cout << "Enter subject: ";
            std::getline(std::cin, lesson);
            if(lesson == "end") {
                break;
            }
            lessons.push_back(lesson);
        }
        schedule[day] = lessons;
        lessons.clear();
    }
    studentData[studentLog].second = schedule;

    std::string ans;
    std::cout << "View updated schedule? (yes/no)\n";
    std::cout << "- ";
    std::getline(std::cin, ans);

    if(ans == "yes") {
        for(const auto &[day, lessons] : studentData[studentLog].second) {
            std::cout << "\nDay: " << day << "\n";
            for(const auto &lesson : lessons) {
                std::cout << " -" << lesson << "\n";
            }
        }
    }
    else if(ans=="no") {
        std::cout << "Exiting...\n"; 
    }
    else {
        std::cout << "Invalid command.\n";
    }
}

void Admin::writeStudentReview() {
    Utils::clearConsole();
    std::cout << "Please enter your name and subject you teach:\n\n";

    std::string teacherName;
    std::string subject;
    std::cout << "   Your name: ";
    std::getline(std::cin, teacherName);

    std::cout << "   Subject you teach: ";
    std::getline(std::cin, subject);
    std::cout << "\n";

    bool validLog = false;
    std::string reviewText;
    std::string studentLog;

    while(!validLog) {
        std::cout << "Enter student username: ";
        std::getline(std::cin, studentLog);
        auto it = studentData.find(studentLog);
        if(it != studentData.end()) {
            std::cout << "\nEnter your review for " << log << "\n";
            std::getline(std::cin, reviewText);
            reviews[studentLog].push_back(std::make_pair(teacherName + " (" + subject + ")", reviewText));
            validLog = true;
        }
        else {
            std::cout << "\nUsername not found, please try again!\n";
            Utils::clearConsole();
        }
    }
    Utils::clearConsole();
    
    std::cout << "Sending review...\n";
    reviews[teacherName].push_back(std::make_pair(subject, reviewText));

    Utils::timeSleepOneSec();
    std::cout << "Review sent!\n";
    Utils::timeSleepOneSec();
    Utils::clearConsole();
}

void Admin::createHomework() {
    Utils::clearConsole();
    bool continueAdding = true;
    
    while(continueAdding) {
        std::string subject;
        std::string homework;

        std::cout << "Enter subject: ";
        std::getline(std::cin, subject);
        
        std::cout << "Enter homework assignment: ";
        std::getline(std::cin, homework);

        std::cout << "\n";
        std::string cont;
        std::cout << "Add more? (yes/no): ";
        std::getline(std::cin, cont);
        std::cout << "\n";

        homeworks[subject] = homework;

        if(cont != "yes") {
            continueAdding = false;
        }
    }

    std::cout << "\nSending assignment...\n";
    Utils::timeSleepOneSec();
    std::cout << "ASSIGNMENT SENT!\n";
    Utils::clearConsole();
}
