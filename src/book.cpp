#include "book.h"

Book::Book(): Item(), author(""), type("") {}

Book::Book(const long& id_, const std::string& name_, const std::string& description_,
           const double& price_, const std::string& author_, const std::string& type_):
Item(id_, name_, description_, price_), author(author_), type(type_) {}

Book::Book(const long& id_, const char* name_, const char* description_,
           const double& price_, const char* author_, const char* type_):
Item(id_, name_, description_, price_), author(author_), type(type_) {}

Book::Book(const Book& other_book): Item(other_book) {
    author = other_book.author;
    type = other_book.type;
}

Book::~Book() {}

void Book::setAuthor(const std::string& author_) noexcept { author = author_; }

void Book::setAuthor(const char* author_) noexcept { author = author_; }

void Book::setType(const std::string& type_) noexcept { author = type_; }

void Book::setType(const char* type_) noexcept { author = type_; }

std::string Book::getAuthor() const noexcept { return author; }

std::string Book::getType() const noexcept { return type; }

std::map<std::string, std::string> Book::getAll() const {
    if (isEmpty())
        throw empty_item("Empty book!");

    std::string id_ = std::to_string(id), price_ = std::to_string(price);
    std::map<std::string, std::string> data =
            {{"ID",          id_},
             {"Name",        name},
             {"Author",      author},
             {"Description", description},
             {"Price",       price_},
             {"Type",        type}};
    return data;
}

bool Book::isEmpty() const {
    if (id == 0 || name.empty() || author.empty() || type.empty() || price == 0.0)
        return true;
    return false;
}

void Book::setAll(std::map<std::string, std::string>& data) {
    id = std::stol(data["ID"]);
    name = data["Name"];
    author = data["Author"];
    description = data["Description"];
    price = std::stod(data["Price"]);
    type = data["Type"];
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
    std::string save =
            data["ID"] + "," + data["Name"] + "," +
            data["Author"] + "," + data["Description"] + "," +
            data["Price"] + "," + data["Type"];
    return save;
}

bool Book::contains(const std::string &str) {
    using namespace std;
    regex pattern = regex(".*" + str + ".*", regex_constants::icase | regex_constants::optimize);
    for (const auto &[key, value]: getAll()) {
        if (regex_search(value, pattern))
            return true;
    }
    return false;
}