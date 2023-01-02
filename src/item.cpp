#include "item.h"

/**
 * @brief Construct a new empty Item object
 * 
 */
Item::Item(): id(0), name(""), description(""), price(0.0) {}

/**
 * @brief Construct a new Item object
 * 
 * @param id_ Item ID
 * @param name_ Item name
 * @param description_ Item description
 * @param price_ Item price
 */
Item::Item(const long& id_, const std::string& name_, const std::string& description_, const double& price_):
id(id_), name(name_), description(description_), price(price_) {}

/**
 * @brief Construct a new Item object
 * 
 * @param id_ Item ID
 * @param name_ Item name
 * @param description_ Item description
 * @param price_ Item price
 */
Item::Item(const long& id_, const char* name_, const char* description_, const double& price_):
id(id_), name(name_), description(description_), price(price_) {}

/**
 * @brief Construct a new Item object from another Item object
 * 
 * @param other Reference to other Item object
 */
Item::Item(const Item& other) {
    id = other.id;
    name = other.name;
    description = other.description;
    price = other.price;
}

Item::~Item() {}

/**
 * @brief Set the ID data
 * 
 * @param id_ Item ID
 */
void Item::setID(const long& id_) { id = id_; }

/**
 * @brief Set the Name data
 * 
 * @param name_ Item name
 */
void Item::setName(const std::string& name_) { name = name_; }

/**
 * @brief Set the Name data
 * 
 * @param name_ Item name
 */
void Item::setName(const char* name_) { name = name_; }

/**
 * @brief Set the Description data
 * 
 * @param description_ Item description
 */
void Item::setDescription(const std::string& description_) { description = description_; }

/**
 * @brief Set the Description data
 * 
 * @param description_ Item description
 */
void Item::setDescription(const char* description_) { description = description_; }

/**
 * @brief Set the Price data
 * 
 * @param price_ Item price
 */
void Item::setPrice(const double& price_) { price = price_; }

/**
 * @brief Get the ID data
 * 
 * @return long Item ID
 */
long Item::getID() const { return id; }

/**
 * @brief Get the Name data
 * 
 * @return std::string Item name
 */
std::string Item::getName() const { return name; }

/**
 * @brief Get the Description data
 * 
 * @return std::string Item description
 */
std::string Item::getDescription() const { return description; }

/**
 * @brief Get the Price data
 * 
 * @return double Item price
 */
double Item::getPrice() const { return price; }

/**
 * @brief Read a long value from the console
 * 
 * @param message Message to display to the user
 * @return long Value read from the console
 */
long Item::readLongValue(const char* message) {
    std::cout << message;
    long value;
    do {
        std::string str;
        std::getline(std::cin, str);
        while (str == "") {
            std::cout << "Invalid input. Please enter a valid number: ";
            std::getline(std::cin, str);
        }
        std::stringstream ss(str);  // create stringstream from input string
        ss >> value;  // extract value from stringstream
        if (value <= 0) {
            std::cout << "Invalid input. Please enter a positive number: ";
        }
    } while (value <= 0);
    return value;
}

/**
 * @brief Read a double value from the console
 * 
 * @param message Message to display to the user
 * @return double Value read from the console
 */
double Item::readDoubleValue(const char* message) {
    std::cout << message;
    double value;
    do {
        std::string str;
        std::getline(std::cin, str);
        while (str == "") {
            std::cout << "Invalid input. Please enter a valid number: ";
            std::getline(std::cin, str);
        }
        std::stringstream ss(str);  // create stringstream from input string
        ss >> value;  // extract value from stringstream
        if (value <= 0) {
            std::cout << "Invalid input. Please enter a positive number: ";
        }
    } while (value <= 0);
    return value;
}

/**
 * @brief Read a string from the console
 * 
 * @param message Message to display to the user
 * @return std::string String read from the console
 */
std::string Item::readString(const char* message) {
    std::string input;
    std::cout << message;
    std::getline(std::cin, input);
    while (input == "" || input == "\n") {
        std::cout << "Invalid input. Please enter a string: ";
        std::getline(std::cin, input);
    }
    return input;
}