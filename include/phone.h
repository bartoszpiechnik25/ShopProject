/**
 * @file phone.h
 * @author bartoszpiechnik25@gmail.com
 * @brief This file contains the implementation of the Phone class.
 * The Phone class is a child class of Item, and provides additional properties for phones such as manufacturer and specs.
 * @version 1.0
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "item.h"
/**
 * @class Phone
 * @brief The Phone class is a child class of Item, and provides additional properties for phones such as manufacturer and specs.
 */
class Phone final: public Item {
private:
    std::string manufacturer;
    std::string specs;

    [[nodiscard]]bool isEmpty() const override;

public:
    /**
     * @brief Default constructor for the Phone class. 
     * Initializes the data members of the class.
     */
    Phone();

    /**
     * @brief Constructor for the Phone class that takes an ID, name, description, price, manufacturer, and specs as arguments.
     * Initializes the data members of the class with the provided values.
     * @param id_ The ID of the phone.
     * @param name_ The name of the phone.
     * @param description_ The description of the phone.
     * @param price_ The price of the phone.
     * @param manufacturer_ The manufacturer of the phone.
     * @param specs_ The specs of the phone.
     */
    Phone(const long &id_, const std::string &name_, const std::string &description_, const double &price_,
          const std::string &manufacturer_,
          const std::string &specs_);

    /**
     * @brief Constructor for the Phone class that takes an ID, name, description, price, manufacturer, and specs as arguments.
     * Initializes the data members of the class with the provided values.
     * @param id_ The ID of the phone.
     * @param name_ The name of the phone, as a C-style string.
     * @param description_ The description of the phone, as a C-style string.
     * @param price_ The price of the phone.
     * @param manufacturer_ The manufacturer of the phone, as a C-style string.
     * @param specs_ The specs of the phone, as a C-style string.
     */
    Phone(const long &id_, const char *name_, const char *description_, const double &price_, const char *manufacturer_,
          const char *specs_);

    /**
     * @brief Copy constructor for the Phone class.
     * Initializes the data members of the class with the values of another Phone object.
     * @param phone The Phone object to copy data from.
     */
    Phone(const Phone &phone);

    /**
     * @brief Destructor for the Phone class.
     */
    ~Phone() final;

    /**
     * @brief Set the manufacturer of the phone
     * @param manufacturer_ The new manufacturer, as a C-style string
     */
    void setManufacturer(const char *manufacturer_) noexcept;

    /**
     * @brief Set the manufacturer of the phone
     * @param manufacturer_ The new manufacturer
     */
    void setManufacturer(const std::string &manufacturer_) noexcept;

    /**
     * @brief Set the specs of the phone
     * @param specs_ The new specs, as a C-style string
     */
    void setSpecs(const char *specs_) noexcept;

    /**
     * @brief Set the specs of the phone
     * @param specs_ The new specs
     */
    void setSpecs(const std::string &specs_) noexcept;

    /**
     * @brief Get the manufacturer of the phone
     * @return A string containing the manufacturer of the phone
     */
    [[nodiscard]]std::string getManufacturer() const noexcept;

    /**
     * @brief Get the specs of the phone
     * @return A string containing the specs of the phone
     */
    [[nodiscard]]std::string getSpecs() const noexcept;

    /**
     * @brief Returns all properties of the phone in a map.
     * @return A map containing all the properties of the phone.
     */
    [[nodiscard]]std::map<std::string, std::string> getAll() const override;

    /**
     * @brief Sets all the properties of the phone from a map.
     * @param data The map containing the properties of the phone.
     */
    void setAll(std::map<std::string, std::string> &) override;

    /**
     * @brief Reads the properties of the phone from a string.
     * @param data The string containing the properties of the phone.
     */
    void readFromStr(std::string &) override;

    /**
     * @brief Check if the phone contains the given string in any of its properties.
     * @param str The string to search for.
     * @return A boolean indicating if the phone contains the given string.
     */
    bool contains(const std::string &str) override;

    /**
     * @brief Saves the properties of the phone to a string in the format for writing to a file.
     * @return A string containing the properties of the phone.
     */
    std::string saveToDatabase() override;
};