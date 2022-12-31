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
     {"Author", author},
     {"Description", description},
     {"Price", price_},
     {"Type", type}};
    return data;
}

bool Book::isEmpty() const {
    if ( author == "" || type == "" || price == 0.0 || id == 0 || description == "" || name == "")
        return true;
    return false;
}

void Book::setAll() {
    id = readLongValue("Enter book ID: ");
    name = readString("Enter book name: ");
    description = readString("Enter book description: ");
    price = readDoubleValue("Enter book price: ");
    author = readString("Enter book author: ");
    type = readString("Enter book type: ");
}

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

std::string Book::saveToDatabase() {
    if (isEmpty())
        throw empty_item("Cannot save empty book!");
    std::map<std::string, std::string> data = getAll();
    std::string save = data["ID"] + "," + data["Name"] + "," + data["Author"] + "," + data["Description"] + "," + data["Price"] + "," + data["Type"];
    // for(const auto&[key, value]: getAll())
    //     save += (value + ",");
    // save.pop_back();
    return save;
}