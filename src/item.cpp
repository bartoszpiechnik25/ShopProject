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

template <typename T>
T getInput(const char* message) {
    T input;
    bool expression = true;
    while (expression) {
        std::cout << message;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if constexpr (std::is_same_v<T, int>)
                expression = (input <= 0);
            else if constexpr (std::is_same_v<T, double>)
                expression = (input <= 0);
            else
                expression = false;
            if (expression)
                std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    return input;
}