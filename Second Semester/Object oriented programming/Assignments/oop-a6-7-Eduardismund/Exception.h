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

class ServiceException : public std::exception {
private:
    std::string message;
public:
    explicit ServiceException(std::string message){
        this->message = std::move(message);
    }
    const char* what() const noexcept override{
        return this->message.c_str();
    }
};