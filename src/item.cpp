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
void Item::setID(const long& id_) noexcept { id = id_; }

/**
 * @brief Set the Name data
 * 
 * @param name_ Item name
 */
void Item::setName(const std::string& name_) noexcept { name = name_; }

/**
 * @brief Set the Name data
 * 
 * @param name_ Item name
 */
void Item::setName(const char* name_) noexcept { name = name_; }

/**
 * @brief Set the Description data
 * 
 * @param description_ Item description
 */
void Item::setDescription(const std::string& description_) noexcept { description = description_; }

/**
 * @brief Set the Description data
 * 
 * @param description_ Item description
 */
void Item::setDescription(const char* description_) noexcept { description = description_; }

/**
 * @brief Set the Price data
 * 
 * @param price_ Item price
 */
void Item::setPrice(const double& price_) noexcept { price = price_; }

/**
 * @brief Get the ID data
 * 
 * @return long Item ID
 */
long Item::getID() const noexcept{ return id; }

/**
 * @brief Get the Name data
 * 
 * @return std::string Item name
 */
std::string Item::getName() const noexcept { return name; }

/**
 * @brief Get the Description data
 * 
 * @return std::string Item description
 */
std::string Item::getDescription() const noexcept { return description; }

/**
 * @brief Get the Price data
 * 
 * @return double Item price
 */
double Item::getPrice() const noexcept { return price; }