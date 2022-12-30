#include "book.h"

Book::Book(): Item(), author(""), type("") {}

Book::Book(const long& id_, const std::string& name_, const std::string& description_, const double& price_, const std::string& author_, const std::string& type_):
Item(id_, name_, description_, price_), author(author_), type(type_) {}

Book::Book(const long& id_, const char* name_, const char* description_, const double& price_, const char* author_, const char* type_):
Item(id_, name_, description_, price_), author(author_), type(type_) {}

Book::Book(const Book& other_book): Item(other_book) {
    author = other_book.author;
    type = other_book.type;
}

Book::~Book() {}

void Book::setAuthor(const std::string& author_) { author = author_; }
void Book::setAuthor(const char* author_) { author = author_; }
void Book::setType(const std::string& type_) { author = type_; }
void Book::setType(const char* type_) { author = type_; }

std::string Book::getAuthor() const { return author; }
std::string Book::getType() const { return type; }

std::map<std::string, std::string> Book::getAll() const {
    if ( isEmpty() )
        throw empty_item("Empty book!");

    std::string id_ = std::to_string(id), price_ = std::to_string(price);
    std::map<std::string, std::string> data = 
     {{"ID", id_},
     {"Name", name},
     {"Description", description},
     {"Price", price_},
     {"Author", author},
     {"Type", type}};
    return data;
}

bool Book::isEmpty() const {
    if ( author == "" || type == "" || price == 0.0 || id == 0 || description == "" || name == "")
        return true;
    return false;
}

void Book::setAll() {
    id = readNumericValue<long>("Enter book ID: ");
    name = readString("Enter book name: ");
    description = readString("Enter book description: ");
    price = readNumericValue<double>("Enter book price: ");
    author = readString("Enter book author: ");
    type = readString("Enter book type: ");
}

void Book::readFromStr(std::stringstream& data) {
    std::vector<std::string> add;
    std::string str;
    while (getline(data, str, ','))
        add.push_back(str);
    author = add[0];
    description = add[1];
    id = std::stol(add[2]);
    name = add[3];
    price = std::stod(add[4]);
    type = add[5];
}

std::stringstream Book::saveToDatabase() {
    if (isEmpty())
        throw empty_item("Cannot save empty book!");
    
    std::string save;
    for(const auto&[key, value]: getAll())
        save += (value + ",");
    save.pop_back();
    return std::stringstream(save);
}


template <typename T>
T readNumericValue(const char* message) {
    std::cout << message;
    T value;
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

std::string readString(const char* message) {
    std::string input;
    std::cout << message;
    std::getline(std::cin, input);
    while (input == "" || input == "\n") {
        std::cout << "Invalid input. Please enter a string: ";
        std::getline(std::cin, input);
    }
    return input;
}
