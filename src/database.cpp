#include "database.h"

std::string ShopDatabase::itemTypeToString(const ItemType& type) const {
    switch (type) {
        case BOOKS:
            return "Books";
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
        stringstream stream(line);
        Item* item = new Book;
        item->readFromStr(stream);
        data[item_type].push_back(item);
    }
    files[type]->close();
}

// void ShopDatabase::open(const std::vector<std::string>& path) {

// }

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
}