#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "user/user.hpp"
#include "data/schedule.hpp"
#include "data/grade.hpp"  // Добавляем включение grade.hpp
#include <unordered_map>
#include <vector>
#include <utility>

class Admin : public User {
private:
    unor_map_vec& studentData;
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& reviews;
    std::unordered_map<std::string, std::string>& homeworks;
    std::unordered_map<std::string, std::pair<std::string, std::string>>& adminMessages;
    std::unordered_map<std::string, std::vector<Grade>>& grades;

public:
    Admin(const std::string& log, const std::string& password, 
          unor_map_vec& studentData,
          std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& reviews,
          std::unordered_map<std::string, std::string>& homework,
          std::unordered_map<std::string, std::pair<std::string, std::string>>& messages,
          std::unordered_map<std::string, std::vector<Grade>>& grades);
    
    void showMenu() override;
    void addStudentGrade();
    void viewMessages();
    void listAllStudents();
    void editStudentSchedule();
    void writeStudentReview();
    void createHomework();
};

#endif
