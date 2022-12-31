#include "phone.h"

Phone::Phone() : Item() {
    manufacturer = "";
    specs = "";
}

Phone::Phone(const long& id_, const std::string& name_, const std::string& description_, const double& price_, const std::string& manufacturer_, const std::string& specs_) : Item(id_, name_, description_, price_) {
    manufacturer = manufacturer_;
    specs = specs_;
}

Phone::Phone(const long& id_, const char* name_, const char* description_, const double& price_, const char* manufacturer_, const char* specs_) : Item(id_, name_, description_, price_) {
    manufacturer = manufacturer_;
    specs = specs_;
}

Phone::Phone(const Phone& phone) : Item(phone.id, phone.name, phone.description, phone.price) {
    manufacturer = phone.manufacturer;
    specs = phone.specs;
}

Phone::~Phone() {}

void Phone::setManufacturer(const char* manufacturer_) { manufacturer = manufacturer_; }
void Phone::setManufacturer(const std::string& manufacturer_) { manufacturer = manufacturer_; }
void Phone::setSpecs(const char* specs_) { specs = specs_; }
void Phone::setSpecs(const std::string& specs_) { specs = specs_; }

std::string Phone::getManufacturer() const { return manufacturer; }
std::string Phone::getSpecs() const { return specs; }

std::map<std::string, std::string> Phone::getAll() const {
    std::map<std::string, std::string> map;
    map["ID"] = std::to_string(id);
    map["Name"] = name;
    map["Manufacturer"] = manufacturer;
    map["Description"] = description;
    map["Price"] = std::to_string(price);
    map["Specs"] = specs;
    return map;
}

void Phone::setAll() {
    id = readLongValue("Enter phone ID: ");
    manufacturer = readString("Enter phone manufacturer: ");
    name = readString("Enter phone model: ");
    description = readString("Enter phone description: ");
    price = readDoubleValue("Enter phone price: ");
    specs = readString("Enter phone specification: ");
}

void Phone::readFromStr(std::string& data) {
    std::vector<std::string> add;
    std::string str;
    std::stringstream source(data);
    while (getline(source, str, ','))
        add.push_back(str);
    id = std::stol(add[0]);
    name = add[1];
    manufacturer = add[2];
    description = add[3];
    price = std::stod(add[4]);
    specs = add[5];
}

std::string Phone::saveToDatabase() {
    if (isEmpty())
        throw empty_item("Cannot save empty book!");
    
    std::map<std::string, std::string> data = getAll();
    std::string save = data["ID"] + "," + data["Name"] + "," + data["Manufacturer"] + "," + data["Description"] + "," + data["Price"] + "," + data["Specs"];
    // for(const auto&[key, value]: getAll())
    //     save += (value + ",");
    // save.pop_back();
    return save;
}

bool Phone::isEmpty() const { return false; }