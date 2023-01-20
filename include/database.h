#pragma once

#include "book.h"
#include "phone.h"

//Define on which item perform database operations
enum ItemType {
    BOOKS,
    PHONES
};
const ItemType initDatabaseItems[] = {BOOKS, PHONES};

class ShopDatabase {
private:
    std::map<ItemType, std::vector<Item *>> data;
    std::map<ItemType, std::map<long, bool>> uniqueID;
    std::map<ItemType, std::vector<std::string>> headers;
    bool *modified;
    std::map<ItemType, std::ifstream *> files;
public:
    ShopDatabase();

    explicit ShopDatabase(const std::map<std::string, ItemType> &paths_);

    explicit ShopDatabase(const std::string &path_, const ItemType &item_type);

    ~ShopDatabase();

    void printDB() const;

    void saveData() noexcept;

    void deleteRecord(const ItemType &item_type, int index);

    void deleteByID(const ItemType &item_type, long ID_);

    ShopDatabase &operator-=(std::pair<ItemType, long> &pair_);

    void addRecord(const ItemType &item_type, Item *new_data);

    void addRecord(const ItemType &item_type, const std::string &str_data);

    ShopDatabase &operator+=(const std::pair<ItemType, std::string> &pair_);

    Item *operator[](const std::pair<ItemType, long> &pair_);

    void sortBy(const ItemType &item_type, const std::string &column_name, bool ascending = true);

    std::map<ItemType, std::vector<Item *>> &getItems();

    [[nodiscard]]std::vector<std::string> getHeaders(const ItemType &item_type) const;

    static Item *selectCorrectChild(const ItemType &) noexcept;

    [[nodiscard]]std::vector<long> getUniqueID(const ItemType &item_type) const;

private:
    void open(const std::string &path, const ItemType &item_type);

    void save(const ItemType &item_type);

    void initMap() noexcept;

    static std::string itemTypeToPath(const ItemType &item_type) noexcept;

    static std::string selectCorrectColumnNames(const ItemType &item_type) noexcept;
};

template <typename K, typename V>
void printMap(const std::map<K, V> &m);