/**
 * @file user.h
 * @author bartoszpiechnik25@gmail.com
 * @brief This file contains the implementation of the User class.
 * The User class is responsible for storing and managing the data for a user of the shop,
 *  such as their username, password, purchase history, and credit balance.
 * @version 1.0
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>

/**
 * @class User
 * @brief The User class is responsible for storing and managing the data for a user of the shop, such as their
 *  username, password, purchase history, and credit balance.
 */
class User {
private:
    std::string username, password;
    std::vector<std::string> history;
    double credits;
public:
    /**
     * @brief Default constructor for the User class.
     * Initializes the data members of the class.
     */
    explicit User();

    /**
     * @brief Constructor for the User class that takes a username, password and money as arguments.
     * Initializes the data members of the class with the provided values.
     * @param username The username of the user.
     * @param passwd The password of the user.
     * @param money The credit balance of the user.
     */
    explicit User(const std::string &username, const std::string &passwd, double money);

    /**
     * @brief Destructor for the User class.
     */
    ~User() = default;

    /**
     * @brief Add credits to the user's balance
     * @param amount The amount of credits to add
     */
    void addCredits(double amount) noexcept;

    /**
     * @brief Subtract credits from the user's balance
     * @param amount The amount of credits to subtract
     */
    void subtractCredits(double amount) noexcept;

    /**
     * @brief Append an item to the user's purchase history
     * @param bought_item The item to append
     */
    void appendHistory(const std::string &bought_item) noexcept;

    /**
     * @brief Get the user's purchase history
     * @return A vector of strings containing the user's purchase history
     */
    [[nodiscard]] const std::vector<std::string> &getHistory() const noexcept;

    /**
     * @brief Get the user's username
     * @return A string containing the user's username
     */
    [[nodiscard]] const std::string &getUsername() const noexcept;

    /**
     * @brief Get the user's password
     * @return A string containing the user's password
     */
    [[nodiscard]] const std::string &getPassword() const noexcept;

    /**
     * @brief Get the user's credit balance
     * @return A double containing the user's credit balance
     */
    [[nodiscard]] double getMoney() const noexcept;

    /**
     * @brief Set the user's password
     * @param passwd The new password
     */
    void setPassword(const std::string &passwd) noexcept;

    /**
     * @brief Save the user's data to a binary file
     * @param file The binary file to save the data to
     */
    void saveToBinary(std::ofstream &file);

    /**
     * @brief Read the user's data from a binary file
     * @param file The binary file to read the data from
     */
    void readFromBinary(std::ifstream &file);
};