#ifndef GRADE_HPP
#define GRADE_HPP

#include <string>
#include <ctime>

struct Grade {
    std::string subject;
    int grade;
    std::string comment;
    std::time_t time;
};

#endif
