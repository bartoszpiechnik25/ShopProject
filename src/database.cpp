#include "database.h"

/**
 * @brief Construct a new Shop Database object
 * 
 */
ShopDatabase::ShopDatabase() {}

/**
 * @brief Construct a new Shop Database object
 * 
 * @param paths_ Map of paths to files with corresponding item type
 */
ShopDatabase::ShopDatabase(const std::map<std::string, ItemType>& paths_) {
    initMap();
    std::vector<std::thread> threads;
    for(const auto& [key, value]: paths_) {
        try {
            threads.emplace_back(std::thread(&ShopDatabase::open, this, key, value));
        } catch (const std::system_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    for(auto& th: threads)
        th.join();
}

/**
 * @brief Construct a new Shop Database object 
 * 
 * @param path_ Path to file
 * @param item_type Type of item
 */
ShopDatabase::ShopDatabase(const std::string& path_, const ItemType& item_type) {
    initMap();
    open(path_, item_type);
}

/**
 * @brief Destroy the Shop Database object
 * 
 */
ShopDatabase::~ShopDatabase() {
    for(const auto& [key, value]: files)
        delete value;
    for(const auto& [key, value]: data) {
        for(Item* it: value)
            delete it;
    }
    delete [] modified;
}

/**
 * @brief Opens file and reads data from it
 * 
 * @param path Path to file
 * @param item_type Type of item
 */
void ShopDatabase::open(const std::string& path, const ItemType& item_type) {
    using namespace std;

    if (files.empty())
        initMap();
    
    files[item_type]->open(path);
    if (files[item_type]->fail()) {
        std::string s = "Cannot open file: %s!" + path;
        throw runtime_error(s.c_str());
    }
    data[item_type] = vector<Item*>();

    string header;
    getline(*files[item_type], header);
    string line;
     
    while (getline(*files[item_type], line)) {
        // stringstream stream(line);
        Item* item = selectCorrectChild(item_type);
        item->readFromStr(line);
        data[item_type].push_back(item);
    }
    files[item_type]->close();
}

/**
 * @brief Prints map
 * 
 */
template <typename K, typename V>
void printMap(const std::map<K, V> &m) {
    for (const auto &[key, value] : m) {
        std::cout << key << ": " << value << std::endl;
    }
    std::cout << std::endl;

}

/**
 * @brief Prints database
 * 
 */
void ShopDatabase::printDB() const {
    for(const auto& [key, value]: data)
        for(Item* it: value)
            printMap<std::string, std::string>(it->getAll());
}

/**
 * @brief Initializes map with ifstream objects and allocates memory for modified array
 * 
 */
void ShopDatabase::initMap() {
    for (const auto& item_num: initDatabaseItems)
        files[item_num] = new std::ifstream;
    modified = new bool[data.size() + 1];
}

/**
 * @brief Delete record from database with specified index
 * 
 * @param item_type Type of item to delete
 * @param index Index of item to delete
 */
void ShopDatabase::deleteRecord(const ItemType& item_type, int index) {
    if (data[item_type].empty())
        throw empty_vector("You want to delete from empty DB!");
    index--;
    if (index < data[item_type].size() && index >= 0) {
        data[item_type].erase(data[item_type].begin() + index);
        modified[item_type] = true;
    }
    else {
        throw std::out_of_range("Index out of range!");
    }
}

/**
 * @brief Deletes record from database with specified index
 * 
 * @param pair_ Pair with type of item and index of item to delete
 * @return ShopDatabase& Reference to database
 */
ShopDatabase& ShopDatabase::operator-=(std::pair<ItemType, int>& pair_) {
    deleteRecord(pair_.first, pair_.second);
    return *this;
}

/**
 * @brief Adds record to database
 * 
 * @param item_type Type of item to add
 */
void ShopDatabase::addRecord(const ItemType& item_type) {
    if (data[item_type].empty())
        throw empty_vector("You want to add to DB that is not loaded!");
    Item* item = selectCorrectChild(item_type);
    item->setAll();
    if (item) {
        data[item_type].push_back(item);
        modified[item_type] = true;
    }
}

/**
 * @brief Adds record to database from string
 * 
 * @param item_type Type of item to add
 * @param str_data String with data to add
 */
void ShopDatabase::addRecordFromStr(const ItemType& item_type, const std::string& str_data) {
    using namespace std;
    if (data[item_type].empty())
        throw empty_vector("You want to add to DB that is not loaded!");
    string line;
    stringstream str_to_be_added(str_data);

    while (getline(str_to_be_added, line)) {
        // stringstream stream(line);
        Item* item = selectCorrectChild(item_type);
        item->readFromStr(line);
        data[item_type].push_back(item);
    }
}

/**
 * @brief Adds record to database
 * 
 * @param item_type Type of item to add
 * @param str_data String with data to add
 * @return ShopDatabase& Reference to this object
 */
ShopDatabase& ShopDatabase::operator+=(const std::pair<ItemType, std::string>& pair_) {
    addRecordFromStr(pair_.first, pair_.second);
    return *this;
}

/**
 * @brief Sorts the database by given column name
 * 
 * @param item_type Type of item to sort
 * @param column_name Column name to sort by
 * @param ascending Ascending or descending order
 */
void ShopDatabase::sortBy(const ItemType& item_type, const std::string& column_name, bool ascending) {
    std::vector<std::string> book_columns = {"ID", "Name", "Author", "Price"};
    std::vector<std::string> phone_columns = {"ID","Name","Manufacturer","Price","Specs"};

    if (data[item_type].empty())
        throw empty_vector("You want to sort empty DB!");
    //check if column_name is valid
    if (item_type == BOOKS) {
        if (std::find(book_columns.begin(), book_columns.end(), column_name) == book_columns.end())
            throw std::invalid_argument("Invalid column name!");
    }
    else if (item_type == PHONES) {
        if (std::find(phone_columns.begin(), phone_columns.end(), column_name) == phone_columns.end())
            throw std::invalid_argument("Invalid column name!");
    }
    else {
        throw std::invalid_argument("Invalid item type!");
    }
    if (column_name == "ID") {
        if (ascending)
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item* a, Item* b) {
                return std::stol(a->getAll().at(column_name)) < std::stol(b->getAll().at(column_name));});
        else
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item* a, Item* b) {
                return std::stol(a->getAll().at(column_name)) > std::stol(b->getAll().at(column_name));});
    }
    else if (column_name == "Price") {
        if (ascending)
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item* a, Item* b) {
                return std::stod(a->getAll().at(column_name)) < std::stod(b->getAll().at(column_name));});
        else
        std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item* a, Item* b) {
            return std::stod(a->getAll().at(column_name)) < std::stod(b->getAll().at(column_name));});
    }
    else {
        if (ascending)
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item* a, Item* b) {
                return a->getAll().at(column_name) < b->getAll().at(column_name);});
        else
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item* a, Item* b) {
                return a->getAll().at(column_name) < b->getAll().at(column_name);});
    }
}

/**
 * @brief Saves the database to the file
 * 
 */
void ShopDatabase::saveData() {
    std::vector<std::thread> threads;
    for(const auto& type: initDatabaseItems) {
        try {
            threads.emplace_back(std::thread(&ShopDatabase::save, this, type));
        } catch (const std::system_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }   
    for(auto& th: threads)
        th.join();
}

/**
 * @brief Saves the database to the file
 * 
 * @param item_type Type of item to save
 *
 * @return std::string 
 */
std::string ShopDatabase::itemTypeToPath(const ItemType& item_type) const {
    switch (item_type) {
        case BOOKS:
            return "../data/books_database.csv";
        case PHONES:
            return "../data/phones_database.csv";
        default:
            return "";
    }
}

/**
 * @brief Saves the database to the file
 * 
 * @param item_type Type of item to save
 */
void ShopDatabase::save(const ItemType& item_type) {
    if (modified[item_type]) {
        std::ofstream save(itemTypeToPath(item_type));
        if (save.good()) {
            std::string a = selectCorrctColumnNames(item_type);
            save << a;
            for(const auto& item_str: data[item_type])
                save << (item_str->saveToDatabase() + "\n");
        } else {
            std::string s = "Cannot open file: %s!" + itemTypeToPath(item_type);
            throw std::runtime_error(s.c_str());
        }
    }
}

/**
 * @brief Selects the correct child class of Item
 * 
 * @param item_type Type of item to load
 * @return Item* 
 */
Item* ShopDatabase::selectCorrectChild(const ItemType& item_type) const {
    switch (item_type) {
        case BOOKS:
            return new Book;
        case PHONES:
            return new Phone;
        default:
            return nullptr;
    }
}

std::string ShopDatabase::selectCorrctColumnNames(const ItemType& item_type) const {
    switch (item_type) {
        case BOOKS:
            return "ID,Name,Author,Description,Price,Type\n";
        case PHONES:
            return "ID,Name,Manufacturer,Description,Price,Specs\n";
        default:
            return "";
    }
}