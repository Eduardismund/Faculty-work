#pragma once
#include <exception>
#include <string>
#include <utility>

class Exception : public std::exception{
private:
    std::string message;
public:
    explicit Exception(std::string setMessage) : message{std::move( setMessage)}{};
    const char* what() const noexcept override{
        return message.c_str();
    }
};