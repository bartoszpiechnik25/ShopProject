#include "database.h"

ShopDatabase::ShopDatabase() {}

ShopDatabase::ShopDatabase(const std::map<std::string, ItemType>& paths_) {
    initMap();
    std::vector<std::thread> threads;
    for (const auto &[key, value]: paths_) {
        try {
            threads.emplace_back(std::thread(&ShopDatabase::open, this, key, value));
        } catch (const std::system_error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::terminate();
        }
    }
    for (auto &th: threads)
        th.join();
}

ShopDatabase::ShopDatabase(const std::string& path_, const ItemType& item_type) {
    initMap();
    open(path_, item_type);
}

ShopDatabase::~ShopDatabase() {
    for (const auto &[key, value]: files)
        delete value;
    for (const auto &[key, value]: data) {
        for (Item *it: value)
            delete it;
    }
    delete[] modified;
}

void ShopDatabase::open(const std::string& path, const ItemType& item_type) {
    using namespace std;

    if (files.empty())
        initMap();

    files[item_type]->open(path);
    if (files[item_type]->fail()) {
        std::string s = "Cannot open file: " + path + "\nCheck the file location.";
        cerr << s + "\nAborting" << endl;
        exit(1);
    }
    data[item_type] = vector<Item *>();

    string header;
    getline(*files[item_type], header);
    stringstream header_stream(header);
    while (getline(header_stream, header, ','))
        headers[item_type].push_back(header);

    string line;
    while (getline(*files[item_type], line)) {
        Item *item = selectCorrectChild(item_type);
        if (!item)
            throw runtime_error("Error allocating memory for Item*!");
        item->readFromStr(line);
        if (uniqueID[item_type].contains(item->getID()))
            throw invalid_argument("ID is not unique!");
        uniqueID[item_type][item->getID()] = true;
        data[item_type].push_back(item);
    }
    files[item_type]->close();
}

template <typename K, typename V>
void printMap(const std::map<K, V> &m) {
    for (const auto &[key, value]: m) {
        std::cout << key << ": " << value << std::endl;
    }
    std::cout << std::endl;
}

void ShopDatabase::printDB() const {
    for(const auto& [key, value]: data)
        for(Item* it: value)
            printMap<std::string, std::string>(it->getAll());
}

void ShopDatabase::initMap() noexcept {
    for (const auto &item_num: initDatabaseItems)
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
    } else {
        throw std::out_of_range("Index out of range!");
    }
}

ShopDatabase& ShopDatabase::operator-=(std::pair<ItemType, long>& pair_) {
    deleteByID(pair_.first, pair_.second);
    return *this;
}

void ShopDatabase::addRecord(const ItemType& item_type, Item* new_data) {
    if (data[item_type].empty())
        throw empty_vector("You want to add to DB that is not loaded!");

    if (new_data) {
        data[item_type].push_back(new_data);
        modified[item_type] = true;
    }
}

void ShopDatabase::addRecord(const ItemType& item_type, const std::string& str_data) {
    using namespace std;
    if (data[item_type].empty())
        throw empty_vector("You want to add to DB that is not loaded!");
    string line;
    stringstream str_to_be_added(str_data);

    while (getline(str_to_be_added, line)) {
        Item *item = selectCorrectChild(item_type);
        item->readFromStr(line);
        data[item_type].push_back(item);
    }
    modified[item_type] = true;
}

ShopDatabase& ShopDatabase::operator+=(const std::pair<ItemType, std::string>& pair_) {
    addRecord(pair_.first, pair_.second);
    return *this;
}

Item* ShopDatabase::operator[](const std::pair<ItemType,long>& pair_) {
    for (auto item: data[pair_.first]) {
        if (item->getID() == pair_.second)
            return item;
    }
    return nullptr;
}

void ShopDatabase::sortBy(const ItemType& item_type, const std::string& column_name, bool ascending) {
    if (data[item_type].empty())
        throw empty_vector("You want to sort empty DB!");

    if (std::find(headers[item_type].begin(), headers[item_type].end(), column_name) == headers[item_type].end())
        throw std::invalid_argument("Invalid column name!");

    if (column_name == "ID") {
        if (ascending)
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item *a, Item *b) {
                return std::stol(a->getAll().at(column_name)) < std::stol(b->getAll().at(column_name));
            });
        else
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item *a, Item *b) {
                return std::stol(a->getAll().at(column_name)) > std::stol(b->getAll().at(column_name));
            });
    } else if (column_name == "Price") {
        if (ascending)
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item *a, Item *b) {
                return std::stod(a->getAll().at(column_name)) < std::stod(b->getAll().at(column_name));
            });
        else
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item *a, Item *b) {
                return std::stod(a->getAll().at(column_name)) > std::stod(b->getAll().at(column_name));
            });
    } else {
        if (ascending)
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item *a, Item *b) {
                return a->getAll().at(column_name) < b->getAll().at(column_name);
            });
        else
            std::sort(data[item_type].begin(), data[item_type].end(), [column_name](Item *a, Item *b) {
                return a->getAll().at(column_name) > b->getAll().at(column_name);
            });
    }
}

std::map<ItemType, std::vector<Item*>>& ShopDatabase::getItems() {
    if (data.empty())
        throw empty_vector("You want to get data from empty DB!");
    return data;
}

std::vector<std::string> ShopDatabase::getHeaders(const ItemType& item_type) const noexcept{
    return headers.at(item_type);
}

void ShopDatabase::saveData() noexcept {
    std::vector<std::thread> threads;
    for (const auto &type: initDatabaseItems) {
        try {
            threads.emplace_back(std::thread(&ShopDatabase::save, this, type));
        } catch (const std::system_error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    for (auto &th: threads)
        th.join();
}

std::string ShopDatabase::itemTypeToPath(const ItemType& item_type) noexcept {
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
            std::string a = selectCorrectColumnNames(item_type);
            save << a;
            for (const auto &item_str: data[item_type])
                save << (item_str->saveToDatabase() + "\n");
        } else {
            std::string s = "Cannot open file: " + itemTypeToPath(item_type) + "!";
            throw std::runtime_error(s.c_str());
        }
    }
}

Item* ShopDatabase::selectCorrectChild(const ItemType& item_type) noexcept {
    switch (item_type) {
        case BOOKS:
            return new Book;
        case PHONES:
            return new Phone;
        default:
            return nullptr;
    }
}

std::string ShopDatabase::selectCorrectColumnNames(const ItemType& item_type) noexcept {
    switch (item_type) {
        case BOOKS:
            return "ID,Name,Author,Description,Price,Type\n";
        case PHONES:
            return "ID,Name,Manufacturer,Description,Price,Specs\n";
        default:
            return "";
    }
}

std::vector<long> ShopDatabase::getUniqueID(const ItemType& item_type) const {
    if (uniqueID.empty())
        throw empty_vector("You want to get unique ID from empty DB!");
    std::vector<long> ids;
    std::for_each(uniqueID.at(item_type).begin(), uniqueID.at(item_type).end(), [&ids](const auto &id) {
        ids.push_back(id.first);
    });
    ids.shrink_to_fit();
    return ids;
}

void ShopDatabase::deleteByID(const ItemType &item_type, const long ID_) {
    auto item = std::find_if(data.at(item_type).begin(), data.at(item_type).end(),
                             [&](auto &element) { return element->getID() == ID_; });

    if (item != data.at(item_type).end()) {
        delete *item;
        data.at(item_type).erase(item);
        modified[item_type] = true;
    } else throw std::invalid_argument("There is no item with this ID!");
}