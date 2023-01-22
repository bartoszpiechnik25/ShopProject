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

void Item::setID(const long& id_) noexcept { id = id_; }

void Item::setName(const std::string& name_) noexcept { name = name_; }

void Item::setName(const char* name_) noexcept { name = name_; }

void Item::setDescription(const std::string& description_) noexcept { description = description_; }

void Item::setDescription(const char* description_) noexcept { description = description_; }

void Item::setPrice(const double& price_) noexcept { price = price_; }

long Item::getID() const noexcept{ return id; }

std::string Item::getName() const noexcept { return name; }

std::string Item::getDescription() const noexcept { return description; }

double Item::getPrice() const noexcept { return price; }