#pragma once

#include "book.h"
#include "phone.h"

//Define on which item perform database operations
enum ItemType {
    ALL,
    BOOKS,
    PHONES
};
const ItemType initDatabaseItems[] = {BOOKS, PHONES};

class ShopDatabase {
private:
    std::map<ItemType, std::vector<Item*>> data;
    bool* modified;
    std::map<ItemType, std::ifstream*> files;
public:
    ShopDatabase();
    ShopDatabase(const std::map<std::string, ItemType>&);
    ShopDatabase(const std::string&, const ItemType);
    ~ShopDatabase();
    void printDB() const;
    void saveData();
    void deleteRecord(const ItemType&, int);
    ShopDatabase& operator-=(std::pair<ItemType, int>&);
    void addRecord(const ItemType&);
    void addRecordFromStr(const ItemType&, const std::string&);
    ShopDatabase& operator+=(const std::pair<ItemType, std::string>&);
    void sortBy(const ItemType&, const std::string&);
    // std::vector<std::unique_ptr<Item>> sortBy(const ItemType&, const std::string&);
    // std::vector<std::unique_ptr<Item>> sortBy(const ItemType&, const int&) const;
private:
    void open(const std::string&, const ItemType&);
    void save(const ItemType&);
    void initMap();
    std::string itemTypeToString(const ItemType&) const;
    std::string itemTypeToPath(const ItemType&) const;
    Item* selectCorrectChild(const ItemType&) const;
};

template <typename K, typename V>
void printMap(const std::map<K, V> &m);