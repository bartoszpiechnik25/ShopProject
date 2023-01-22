/**
 * @file item.h
 * @author bartoszpiechnik25@gmail.com
 * @brief This file contains the implementation of the Item class.
 * The Item class is the base class for books and phones, and provides a common interface for handling the basic
 * properties of an item such as ID, name, description and price.
 * @version 1.0
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <limits>
#include <thread>
#include <map>
#include <regex>
#include <algorithm>
#include "exception.h"

/**
 * @class Item
 * @brief The Item class is the base class for books and phones, and provides a common interface for handling the basic
 * properties of an item such as ID, name, description and price.
 */
class Item {
protected:
    long id;
    std::string name;
    std::string description;
    double price;

    /**
     * @brief Check if the item is empty
     * @return A boolean indicating if the item is empty.
    */
    [[nodiscard]]virtual bool isEmpty() const = 0;

public:
    /**
     * @brief Default constructor for the Item class.
     * Initializes the data members of the class.
     */
    Item();

    /**
     * @brief Constructor for the Item class that takes an ID, name, description, and price as arguments.
     * Initializes the data members of the class with the provided values.
     * @param id_ The ID of the item.
     * @param name_ The name of the item.
     * @param description_ The description of the item.
     * @param price_ The price of the item.
     */
    Item(const long &id_, const std::string &name_, const std::string &description_, const double &price_);

    /**
     * @brief Constructor for the Item class that takes an ID, name, description, and price as arguments.
     * Initializes the data members of the class with the provided values.
     * @param id_ The ID of the item.
     * @param name_ The name of the item.
     * @param description_ The description of the item.
     * @param price_ The price of the item.
     */
    Item(const long &id_, const char *name_, const char *description_, const double &price_);

    /**
     * @brief Copy constructor for the Item class.
     * Initializes the data members of the class with the values from the other item.
     * @param other The other item.
     */
    Item(const Item &other);

    /**
     * @brief Destructor for the Item class.
     */
    virtual ~Item() = 0;

    /**
     * @brief Sets the ID of the item.
     * @param id_ The new ID.
     */
    void setID(const long &id_) noexcept;

    /**
     * @brief Sets the name of the item.
     * @param name_ The new name.
     */
    void setName(const std::string &name_) noexcept;

    /**
     * @brief Sets the name of the item.
     * @param name_ The new name.
     */
    void setName(const char *name_) noexcept;

    /**
     * @brief Sets the description of the item.
     * @param description_ The new description.
     */
    void setDescription(const std::string &description_) noexcept;

    /**
     * @brief Sets the description of the item.
     * @param description_ The new description.
     */
    void setDescription(const char *description_) noexcept;

    /**
     * @brief Sets the price of the item.
     * @param price_ The new price.
     */
    void setPrice(const double &price_) noexcept;

    /**
     * @brief Returns the ID of the item.
     * @return The ID of the item.
     */
    [[nodiscard]]long getID() const noexcept;

    /**
     * @brief Returns the name of the item.
     * @return The name of the item.
     */
    [[nodiscard]]std::string getName() const noexcept;

    /**
     * @brief Returns the description of the item.
     * @return The description of the item.
     */
    [[nodiscard]]std::string getDescription() const noexcept;

    /**
     * @brief Returns the price of the item.
     * @return The price of the item.
     */
    [[nodiscard]]double getPrice() const noexcept;

    /**
     * @brief Returns all properties of the item in a map.
     * @return A map containing all the properties of the item.
     */
    [[nodiscard]]virtual std::map<std::string, std::string> getAll() const = 0;

    /**
     * @brief Sets all the properties of the item from a map.
     * @param data The map containing the properties of the item.
     */
    virtual void setAll(std::map<std::string, std::string> &data) = 0;

    /**
     * @brief Reads the properties of the item from a string.
     * @param data The string containing the properties of the item.
     */
    virtual void readFromStr(std::string &data) = 0;

    /**
     * @brief Saves the properties of the item to a string in the format for writing to a file.
     * @return A string containing the properties of the item.
     */
    virtual std::string saveToDatabase() = 0;

    /**
     * @brief Check if the item contains the given string in any of its properties.
     * @param str The string to search for.
     * @return A boolean indicating if the item contains the given string.
     */
    virtual bool contains(const std::string &str) = 0;
};