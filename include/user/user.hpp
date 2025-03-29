#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "utils/utils.hpp"

class User {
protected:
    std::string log;
    std::string password;
    
public:
    User(const std::string& log, const std::string& password);
    virtual ~User();
    
    virtual void showMenu() = 0;
    void personalAccount();
    User* updateData();
};

#endif
