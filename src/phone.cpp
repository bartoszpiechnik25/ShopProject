#include "phone.h"

/**
 * @brief Construct a new empty Phone object
 * 
 */
Phone::Phone() : Item() {
    manufacturer = "";
    specs = "";
}

/**
 * @brief Construct a new Phone object
 * 
 * @param id_ Phone ID
 * @param name_ Phone name
 * @param description_ Phone description
 * @param price_ Phone price
 * @param manufacturer_ Phone manufacturer
 * @param specs_ Phone specs
 */
Phone::Phone(const long& id_, const std::string& name_, const std::string& description_, const double& price_, const std::string& manufacturer_, const std::string& specs_) : Item(id_, name_, description_, price_) {
    manufacturer = manufacturer_;
    specs = specs_;
}

/**
 * @brief Construct a new Phone object
 * 
 * @param id_ Phone ID
 * @param name_ Phone name
 * @param description_ Phone description
 * @param price_ Phone price
 * @param manufacturer_ Phone manufacturer
 * @param specs_ Phone specs
 */
Phone::Phone(const long& id_, const char* name_, const char* description_, const double& price_, const char* manufacturer_, const char* specs_) : Item(id_, name_, description_, price_) {
    manufacturer = manufacturer_;
    specs = specs_;
}

/**
 * @brief Construct a new Phone object from another Phone object
 * 
 * @param phone Reference to other Phone object
 */
Phone::Phone(const Phone& phone) : Item(phone.id, phone.name, phone.description, phone.price) {
    manufacturer = phone.manufacturer;
    specs = phone.specs;
}

/**
 * @brief Destroy the Phone object
 * 
 */
Phone::~Phone() {}

/**
 * @brief Set the Manufacturer data
 * 
 * @param manufacturer_ Phone manufacturer
 */
void Phone::setManufacturer(const char* manufacturer_) { manufacturer = manufacturer_; }

/**
 * @brief Set the Manufacturer data
 * 
 * @param manufacturer_ Phone manufacturer
 */
void Phone::setManufacturer(const std::string& manufacturer_) { manufacturer = manufacturer_; }

/**
 * @brief Set the Specs data
 * 
 * @param specs_ Phone specs
 */
void Phone::setSpecs(const char* specs_) { specs = specs_; }

/**
 * @brief Set the Specs data
 * 
 * @param specs_ Phone specs
 */
void Phone::setSpecs(const std::string& specs_) { specs = specs_; }

/**
 * @brief Get the Manufacturer data
 * 
 * @return std::string Phone manufacturer
 */
std::string Phone::getManufacturer() const { return manufacturer; }

/**
 * @brief Get the Specs data
 * 
 * @return std::string Phone specs
 */
std::string Phone::getSpecs() const { return specs; }

/**
 * @brief Get all data
 * 
 * @return std::map<std::string, std::string> Map of all data
 */
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

/**
 * @brief Set all data from user input
 * 
 */
void Phone::setAll(std::map<std::string, std::string>& data) {
    id = stol(data["ID"]);
    manufacturer = data["Manufacturer"];
    name = data["Name"];
    description = data["Description"];
    price = stod(data["Price"]);
    specs = data["Specs"];
}

/**
 * @brief Reads data from string and sets it to the object
 * 
 * @param data String with data
 */
void Phone::readFromStr(std::string& data) {
    std::vector<std::string> add;
    std::string str;
    std::stringstream source(data);
    while (getline(source, str, ','))
        add.push_back(str);
    try {
        id = std::stol(add[0]);
    }catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "There is an error with columns in database" << std::endl;
        std::cerr << "Perhaps description contains commas?" << std::endl;
        std::cerr << "Error in line:\n";
        for_each(add.begin(), add.end(), [](std::string& x){ std::cerr<< x << " ";});
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    name = add[1];
    manufacturer = add[2];
    description = add[3];
    try {
        price = std::stod(add[4]);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "There is an error with columns in database" << std::endl;
        std::cerr << "Perhaps description contains commas?" << std::endl;
        std::cerr << "Error in line:\n";
        for_each(add.begin(), add.end(), [](std::string& x){ std::cerr<< x << " ";});
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    specs = add[5];
}

/**
 * @brief Convert object to comma separated string
 * 
 * @return std::string Commas separated string of all data from object
 */
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

/**
 * @brief Check if object is empty
 * 
 * @return true Object is empty
 * @return false Object is not empty
 */
bool Phone::isEmpty() const {
    if (id == 0 || name.empty() || manufacturer.empty() || price == 0 || specs.empty())
        return true;
    return false;
}

/**
 * @brief Search all fields in the class for specified pattern.
 * @param str Pattern to be found in the fields;
 * @return True if pattern was found otherwise false.
 */
bool Phone::contains(const std::string &str) {
    using namespace std;
    regex pattern = regex(".*" + str + ".*", regex_constants::icase | regex_constants::optimize);
    for (const auto &[key, value]: getAll()) {
        if (regex_match(value, pattern))
            return true;
    }
    return false;
}