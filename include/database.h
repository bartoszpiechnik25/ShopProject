#pragma once

#include "book.h"

//Define on which item perform database ItemType
enum ItemType {
    ALL,
    BOOKS,
};
const ItemType initDatabaseItems[] = {BOOKS};

class ShopDatabase {
private:
    std::map<std::string, std::vector<Item*>> data;
    bool modified = false;
    std::map<ItemType, std::ifstream*> files;
    void open(const std::string&, const ItemType&);
    // void open(const std::vector<std::string>&);
    void initMap();
    std::string itemTypeToString(const ItemType&) const;
public:
    ShopDatabase();
    ShopDatabase(const std::map<std::string, ItemType>&);
    ShopDatabase(const std::string&, const ItemType);
    ~ShopDatabase();
    void printDB() const;
    // void loadData(const int&);
    // void saveData(const int&);
    // void modifyRecord();
};

template <typename K, typename V>
void printMap(const std::map<K, V> &m);