#include "book.h"

/**
 * @brief Construct a new empty Book object    
 * 
 */
Book::Book(): Item(), author(""), type("") {}

/**
 * @brief Construct a new Book object
 * 
 * @param id_ Book ID
 * @param name_ Book name
 * @param description_ Book description
 * @param price_ Book price
 * @param author_ Book author
 * @param type_ Book type
 */
Book::Book(const long& id_, const std::string& name_, const std::string& description_, const double& price_, const std::string& author_, const std::string& type_):
Item(id_, name_, description_, price_), author(author_), type(type_) {}

/**
 * @brief Construct a new Book object
 * 
 * @param id_ Book ID
 * @param name_ Book name
 * @param description_ Book description
 * @param price_ Book price
 * @param author_ Book author
 * @param type_ Book type
 */
Book::Book(const long& id_, const char* name_, const char* description_, const double& price_, const char* author_, const char* type_):
Item(id_, name_, description_, price_), author(author_), type(type_) {}

/**
 * @brief Construct a new Book object    
 * 
 * @param other_book Reference to other Book object
 */
Book::Book(const Book& other_book): Item(other_book) {
    author = other_book.author;
    type = other_book.type;
}

/**
 * @brief Destroy the Book object
 * 
 */
Book::~Book() {}

/**
 * @brief Set the ID data
 * 
 * @param id_ Book ID
 */
void Book::setAuthor(const std::string& author_) { author = author_; }

/**
 * @brief Set the Author data
 * 
 * @param id_ Book author
 */
void Book::setAuthor(const char* author_) { author = author_; }

/**
 * @brief Set the Type data
 * 
 * @param id_ Book type
 */
void Book::setType(const std::string& type_) { author = type_; }

/**
 * @brief Set the Type data
 * 
 * @param id_ Book type
 */
void Book::setType(const char* type_) { author = type_; }

/**
 * @brief Get the Author data
 * 
 * @return std::string Book author
 */
std::string Book::getAuthor() const { return author; }

/**
 * @brief Get the Type data
 * 
 * @return std::string Book type
 */
std::string Book::getType() const { return type; }

/**
 * @brief Get all data from object
 * 
 * @return std::map<std::string, std::string> Map with all data from object
 */
std::map<std::string, std::string> Book::getAll() const {
    if ( isEmpty() )
        throw empty_item("Empty book!");

    std::string id_ = std::to_string(id), price_ = std::to_string(price);
    std::map<std::string, std::string> data = 
     {{"ID", id_},
     {"Name", name},
     {"Author", author},
     {"Description", description},
     {"Price", price_},
     {"Type", type}};
    return data;
}

/**
 * @brief Check if object is empty
 * 
 * @return true If object is empty
 */
bool Book::isEmpty() const {
    if (id == 0 || name.empty() || author.empty() || type.empty() || price == 0.0)
        return true;
    return false;
}

/**
 * @brief Read all data from user
 * 
 */
void Book::setAll(std::map<std::string, std::string>& data) {
    id = std::stol(data["ID"]);
    name = data["Name"];
    author = data["Author"];
    description = data["Description"];
    price = std::stod(data["Price"]);
    type = data["Type"];
}

/**
 * @brief Read all data from string
 * 
 * @param data Comma separated string with data
 */
void Book::readFromStr(std::string& data) {
    std::vector<std::string> add;
    std::string str;
    std::stringstream source(data);
    while (getline(source, str, ','))
        add.push_back(str);
    try {
        id = std::stol(add[0]);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "There is an error with columns in database" << std::endl;
        std::cerr << "Perhaps description contains commas?" << std::endl;
        std::cerr << "Error in line:\n";
        for_each(add.begin(), add.end(), [](std::string& x){ std::cerr<< x << " ";});
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }
    name = add[1];
    author = add[2];
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
    type = add[5];
}

/**
 * @brief Save all data to string
 * 
 * @return std::string String with all data
 */
std::string Book::saveToDatabase() {
    if (isEmpty())
        throw empty_item("Cannot save empty book!");
    std::map<std::string, std::string> data = getAll();
    std::string save =
     data["ID"] + "," + data["Name"] + "," + 
     data["Author"] + "," + data["Description"] + "," + 
     data["Price"] + "," + data["Type"];
    return save;
}

void Book::saveToBinary(std::ofstream & out) {
    out.write(reinterpret_cast<char*>(&id), sizeof(id));
    out.write(reinterpret_cast<char*>(&price), sizeof(price));
    int name_size = name.size(), author_size = author.size(), description_size = description.size(), type_size = type.size();
    out.write(reinterpret_cast<char*>(&type_size), sizeof(type_size));
    out.write(&type[0], type_size);
    out.write(reinterpret_cast<char*>(&author_size), sizeof(author_size));
    out.write(&author[0], author_size);
    out.write(reinterpret_cast<char*>(&name_size), sizeof(name_size));
    out.write(&name[0], name_size);
    out.write(reinterpret_cast<char*>(&description_size), sizeof(description_size));
    out.write(&description[0], description_size);
}

void Book::readBinary(std::ifstream & in) {
    int name_size, author_size, description_size, type_size;
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(reinterpret_cast<char*>(&price), sizeof(price));
    in.read(reinterpret_cast<char*>(&type_size), sizeof(type_size));
    type.resize(type_size);
    in.read(&type[0], type_size);
    in.read(reinterpret_cast<char*>(&author_size), sizeof(author_size));
    author.resize(author_size);
    in.read(&author[0], author_size);
    in.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));
    name.resize(name_size);
    in.read(&name[0], name_size);
    in.read(reinterpret_cast<char*>(&description_size), sizeof(description_size));
    description.resize(description_size);
    in.read(&description[0], description_size);
}

/**
 * @brief Search all fields in the class for specified pattern.
 * @param str Pattern to be found in the fields;
 * @return True if pattern was found otherwise false.
 */
bool Book::contains(const std::string &str) {
    using namespace std;
    regex pattern = regex(".*" + str + ".*", regex_constants::icase|regex_constants::optimize);
    for (const auto &[key, value]: getAll()) {
        if (regex_search(value, pattern))
            return true;
    }
    return false;
}