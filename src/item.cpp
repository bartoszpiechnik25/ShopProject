#include "item.h"

Item::Item(): id(0), name(""), description(""), price(0.0) {}

Item::Item(const long& id_, const std::string& name_, const std::string& description_, const double& price_):
id(id_), name(name_), description(description_), price(price_) {}

Item::Item(const long& id_, const char* name_, const char* description_, const double& price_):
id(id_), name(name_), description(description_), price(price_) {}

Item::Item(const Item& other) {
    id = other.id;
    name = other.name;
    description = other.description;
    price = other.price;
}

Item::~Item() {}

void Item::setID(const long& id_) { id = id_; }
void Item::setName(const std::string& name_) { name = name_; }
void Item::setName(const char* name_) { name = name_; }
void Item::setDescription(const std::string& description_) { description = description_; }
void Item::setDescription(const char* description_) { description = description_; }
void Item::setPrice(const double& price_) { price = price_; }
long Item::getID() const { return id; }
std::string Item::getName() const { return name; }
std::string Item::getDescription() const { return description; }
double Item::getPrice() const { return price; }

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