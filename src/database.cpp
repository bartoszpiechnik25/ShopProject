#include "database.h"

ShopDatabase::ShopDatabase() {}

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

ShopDatabase& ShopDatabase::operator-=(std::pair<ItemType, int>& pair_) {
    deleteRecord(pair_.first, pair_.second);
    return *this;
}

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

ShopDatabase& ShopDatabase::operator+=(const std::pair<ItemType, std::string>& pair_) {
    addRecordFromStr(pair_.first, pair_.second);
    return *this;
}

void ShopDatabase::sortBy(const ItemType& item_type, const std::string& column_name) {
    std::vector<std::string> book_columns = {"ID", "Name", "Author", "Price"};
    std::vector<std::string> phone_columns = {"ID","Name","Manufacturer","Price","Specs"};

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
    if (column_name == "ID")
        std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item* a, Item* b) {
            return std::stol(a->getAll().at(column_name)) < std::stol(b->getAll().at(column_name));});
    else if (column_name == "Price")
        std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item* a, Item* b) {
            return std::stod(a->getAll().at(column_name)) < std::stod(b->getAll().at(column_name));});
    else
        std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item* a, Item* b) {
            return a->getAll().at(column_name) < b->getAll().at(column_name);});
}

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
            for(const auto& item_str: data[item_type])
                save << (item_str->saveToDatabase() + "\n");
        } else {
            std::string s = "Cannot open file: %s!" + itemTypeToPath(item_type);
            throw std::runtime_error(s.c_str());
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

// void ShopDatabase::emplaceItemBack(const ItemType& item_type, std::string data_) {
//     switch (item_type) {
//         case BOOKS:
//             return new Book;
//         case PHONES:
//             return new Phone;
//         default:
//             return nullptr;
//     }
// }