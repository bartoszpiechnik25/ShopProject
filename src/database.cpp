#include "database.h"

std::string ShopDatabase::itemTypeToString(const ItemType& type) const {
    switch (type) {
        case BOOKS:
            return "Books";
        case PHONES:
            return "Phones";
        default:
            return "";
    }
}

ShopDatabase::ShopDatabase() {}

ShopDatabase::ShopDatabase(const std::map<std::string, ItemType>& paths_) {
    initMap();
    std::vector<std::thread> threads;
    for(const auto& [key, value]: paths_)
        threads.push_back(std::thread(&ShopDatabase::open, this, key, value));
    for(auto& th: threads)
        th.join();
}

ShopDatabase::ShopDatabase(const std::string& path_, const ItemType item_type) {
    initMap();
    open(path_, item_type);
}

ShopDatabase::~ShopDatabase() {
    for(const auto& [key, value]: files)
        delete value;
    for(const auto& [key, value]: data) {
        for(Item* it: value)
            delete it;
    }
    delete [] modified;
}

void ShopDatabase::open(const std::string& path, const ItemType& type) {
    using namespace std;
    string item_type = itemTypeToString(type);

    if (files.empty())
        initMap();
    
    files[type]->open(path);
    if (files[type]->fail()) {
        char* s;
        sprintf(s, "Cannot open file: %s!", path.c_str());
        throw runtime_error(s);
    }
    data[item_type] = vector<Item*>();

    string header;
    getline(*files[type], header);
    string line;
     
    while (getline(*files[type], line)) {
        // stringstream stream(line);
        Item* item = selectCorrectChild(type);
        item->readFromStr(line);
        data[item_type].push_back(item);
    }
    files[type]->close();
}

template <typename K, typename V>
void printMap(const std::map<K, V> &m) {
    for (const auto &[key, value] : m) {
        std::cout << key << ": " << value << std::endl;
    }
    std::cout << std::endl;

}

void ShopDatabase::printDB() const {
    for(const auto& [key, value]: data)
        for(Item* it: value)
            printMap<std::string, std::string>(it->getAll());
}

void ShopDatabase::initMap() {
    for (const auto& item_num: initDatabaseItems)
        files[item_num] = new std::ifstream;
    modified = new bool[data.size() + 1];
}

void ShopDatabase::deleteRecord(const ItemType& item_type, int index) {
    std::string type = itemTypeToString(item_type);
    if (data[type].empty())
        throw empty_vector("You want to delete from empty DB!");
    index--;
    if (index < data[type].size() && index >= 0) {
        data[type].erase(data[type].begin() + index);
        modified[item_type] = true;
    }
    else {
        throw std::out_of_range("Index out of range!");
    }
}

ShopDatabase& ShopDatabase::operator-=(std::pair<ItemType, int>& pair_) {
    deleteRecord(pair_.first, pair_.second);
    return *this;
}

void ShopDatabase::addRecord(const ItemType& item_type) {
    std::string type = itemTypeToString(item_type);
    if (data[type].empty())
        throw empty_vector("You want to add to DB that is not loaded!");
    Item* item = selectCorrectChild(item_type);
    item->setAll();
    if (item) {
        data[type].push_back(item);
        modified[item_type] = true;
    }
}

void ShopDatabase::saveData() {
    std::vector<std::thread> threads;
    for(const auto& type: initDatabaseItems)
        threads.push_back(std::thread(&ShopDatabase::save, this, type));
    for(auto& th: threads)
        th.join();
}

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

void ShopDatabase::save(const ItemType& item_type) {
    if (modified[item_type]) {
        std::ofstream save(itemTypeToPath(item_type));
        if (save.good()) {
            std::string a = "Author,Description,ID,Name,Price,Type\n";
            save << a;
            for(const auto& item_str: data[itemTypeToString(item_type)])
                save << (item_str->saveToDatabase() + "\n");
        } else {
            char* s;
            sprintf(s, "Cannot open file: %s!", itemTypeToPath(item_type).c_str());
            throw std::runtime_error(s);
        }
    }
}

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