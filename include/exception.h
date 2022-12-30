#pragma once

#include <exception>
#include <string>

class empty_item: public std::exception {
private:
    std::string message;
public:
    empty_item(std::string m): message(m) {}
    const char* what() const throw() { return message.c_str(); }
};