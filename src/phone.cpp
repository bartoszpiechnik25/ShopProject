#include "phone.h"

Phone::Phone() : Item() {
    manufacturer = "";
    specs = "";
}

Phone::Phone(const long& id_, const std::string& name_, const std::string& description_,
             const double& price_, const std::string& manufacturer_, const std::string& specs_):
             Item(id_, name_, description_, price_), specs(specs_), manufacturer(manufacturer_) {}

Phone::Phone(const long& id_, const char* name_, const char* description_, const double& price_, const char* manufacturer_, const char* specs_) : Item(id_, name_, description_, price_) {
    manufacturer = manufacturer_;
    specs = specs_;
}

Phone::Phone(const Phone& phone) : Item(phone.id, phone.name, phone.description, phone.price) {
    manufacturer = phone.manufacturer;
    specs = phone.specs;
}

Phone::~Phone() {}

void Phone::setManufacturer(const char* manufacturer_) noexcept { manufacturer = manufacturer_; }

void Phone::setManufacturer(const std::string& manufacturer_) noexcept { manufacturer = manufacturer_; }

void Phone::setSpecs(const char* specs_) noexcept { specs = specs_; }

void Phone::setSpecs(const std::string& specs_) noexcept { specs = specs_; }

std::string Phone::getManufacturer() const noexcept { return manufacturer; }

std::string Phone::getSpecs() const noexcept { return specs; }

std::map<std::string, std::string> Phone::getAll() const {
    if (isEmpty())
        throw empty_item("Empty phone!");

    std::map<std::string, std::string> map;
    map["ID"] = std::to_string(id);
    map["Name"] = name;
    map["Manufacturer"] = manufacturer;
    map["Description"] = description;
    map["Price"] = std::to_string(price);
    map["Specs"] = specs;
    return map;
}

void Phone::setAll(std::map<std::string, std::string>& data) {
    id = stol(data["ID"]);
    manufacturer = data["Manufacturer"];
    name = data["Name"];
    description = data["Description"];
    price = stod(data["Price"]);
    specs = data["Specs"];
}

void Phone::readFromStr(std::string& data) {
    std::vector<std::string> add;
    std::string str;
    std::stringstream source(data);
    while (getline(source, str, ','))
        add.push_back(str);
    try {
        id = std::stol(add[0]);
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "There is an error with columns in database" << std::endl;
        std::cerr << "Perhaps description contains commas?" << std::endl;
        std::cerr << "Error in line:\n";
        for_each(add.begin(), add.end(), [](std::string &x) { std::cerr << x << " "; });
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    name = add[1];
    manufacturer = add[2];
    description = add[3];
    try {
        price = std::stod(add[4]);
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "There is an error with columns in database" << std::endl;
        std::cerr << "Perhaps description contains commas?" << std::endl;
        std::cerr << "Error in line:\n";
        for_each(add.begin(), add.end(), [](std::string &x) { std::cerr << x << " "; });
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    specs = add[5];
}

std::string Phone::saveToDatabase() {
    if (isEmpty())
        throw empty_item("Cannot save empty book!");

    std::map<std::string, std::string> data = getAll();
    std::string save = data["ID"] + "," + data["Name"] + "," + data["Manufacturer"] + "," + data["Description"] + "," +
                       data["Price"] + "," + data["Specs"];
    return save;
}

bool Phone::isEmpty() const {
    if (id == 0 || name.empty() || manufacturer.empty() || price == 0 || specs.empty())
        return true;
    return false;
}

bool Phone::contains(const std::string &str) {
    using namespace std;
    regex pattern = regex(".*" + str + ".*", regex_constants::icase | regex_constants::optimize);
    for (const auto &[key, value]: getAll()) {
        if (regex_match(value, pattern))
            return true;
    }
    return false;
}