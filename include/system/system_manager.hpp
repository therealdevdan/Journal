#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>
#include <exception>

namespace MyExceptions {
    class ErrorAnswerUser : public std::exception {
    public:
        ErrorAnswerUser() noexcept = default;
        ErrorAnswerUser(const char* e) noexcept : msg(e) {}
        ErrorAnswerUser(const ErrorAnswerUser& other) noexcept : msg(other.msg) {}
        
        const char* what() const noexcept override {
            return msg.c_str();                
        }

        virtual ~ErrorAnswerUser() noexcept {}
    
    protected:
        std::string msg;
    };

    class ErrorAnswerAdmin : public ErrorAnswerUser {
    public:
        ErrorAnswerAdmin(const char* e) noexcept : ErrorAnswerUser(e) {}
        ErrorAnswerAdmin(const ErrorAnswerAdmin& other) noexcept : ErrorAnswerUser(other) {}
        virtual ~ErrorAnswerAdmin() noexcept {}
    };
};

#endif
