/**
 * @file exception.h
 * @author bartoszpiechnik25@gmail.com
 * @brief This file contains the implementation of the empty_item and empty_vector exception classes.
 * @version 1.0
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <exception>
#include <string>

/**
 * @class empty_item 
 * @brief An exception class that is thrown when an item is empty.
 * The empty_item exception class is thrown when an item is empty, indicating that it does not contain any valid data.
 */
class empty_item: public std::exception {
private:
    std::string message;
public:
    /**
     * @brief Constructor for the empty_item class that takes an error message as an argument.
     * @param m The error message to be passed along with the exception.
     */
    explicit empty_item(std::string m) : message(m) {}

    /**
     * @brief Returns the error message associated with the exception.
     * @return A C-style string containing the error message.
     */
    const char *what() const throw() { return message.c_str(); }
};

/**
 * @class empty_vector
 * @brief An exception class that is thrown when a vector is empty.
 * The empty_vector exception class is thrown when a vector is empty, indicating that it does not contain any valid data.
 */
class empty_vector: public std::exception {
private:
    std::string message;
public:
    /**
     * @brief Constructor for the empty_vector class that takes an error message as an argument.
     * @param m The error message to be passed along with the exception.
     */
    explicit empty_vector(std::string m) : message(m) {}

    /**
     * @brief Returns the error message associated with the exception.
     * @return A C-style string containing the error message.
     */
    const char *what() const throw() { return message.c_str(); }
};