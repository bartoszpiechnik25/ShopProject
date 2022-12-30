#pragma once

#include "book.h"

class ShopDatabase {
private:
    std::map<std::string, std::vector<Item*>> data;
    bool modified = false;
    std::vector<std::ifstream> files;
    void open(const std::string&);
    void open(const std::vector<std::string>&);
public:
    ShopDatabase();
    ShopDatabase(const std::vector<std::string>&);
    ShopDatabase(const std::string&);
    ~ShopDatabase();
    void printDB() const;
    // void loadData(const int&);
    // void saveData(const int&);
    // void modifyRecord();
};

template <typename K, typename V>
void printMap(const std::map<K, V> &m);