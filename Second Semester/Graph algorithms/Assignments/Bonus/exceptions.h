
#ifndef UNTITLED3_EXCEPTIONS_H
#define UNTITLED3_EXCEPTIONS_H

#endif //UNTITLED3_EXCEPTIONS_H

#include <exception>
#include <string>

class GraphException: public std::exception {
private:
    const std::string exception_msg;
public:
    explicit GraphException(std::string msg);
    virtual const char* what();
};