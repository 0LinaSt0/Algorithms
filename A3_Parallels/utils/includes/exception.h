#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

namespace s21{

class Exception : public std::exception{
public:
    Exception() = delete;
    Exception(const Exception&) = delete;
    Exception(Exception&&) = delete;
    Exception(const std::string& msg);
    ~Exception() = default;

    Exception& operator=(const Exception&) = delete;
    Exception& operator=(Exception&&) = delete;

    virtual std::string GetMessage() const = 0;

protected:
    std::string msg_;

};

}

#endif
