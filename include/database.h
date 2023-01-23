/**
* @file database.h
* @author bartoszpiechnik25@gmail.com
* @brief This file contains the implementation of the ShopDatabase class.
* The ShopDatabase class provides an interface for performing database operations on books and phones.
* The class uses std::map and std::vector to store the data internally and provides various methods for adding,
* deleting, and modifying the data. The class also provides a mechanism for loading and saving the data from and
* to files.
* @version 1.0
* @date 2023-01-22
*
* @copyright Copyright (c) 2023
*
*/

#pragma once

#include "book.h"
#include "phone.h"

//Define on which item perform database operations
enum ItemType {
    BOOKS,
    PHONES
};
const ItemType initDatabaseItems[] = {BOOKS, PHONES};


/**
 * @class ShopDatabase
 * @brief The ShopDatabase class provides an interface for performing database operations on books and phones.
 */
class ShopDatabase {
private:
    std::map<ItemType, std::vector<Item *>> data;
    std::map<ItemType, std::map<long, bool>> uniqueID;
    std::map<ItemType, std::vector<std::string>> headers;
    bool *modified;
    std::map<ItemType, std::ifstream *> files;
public:
    /**

     * @brief Default constructor for the ShopDatabase class.
     * Initializes the data members of the class.
     */
    ShopDatabase();

    /**
     * @brief Constructor for the ShopDatabase class that takes a map of file paths and item types.
     * Initializes the data members of the class and loads the data from the specified files.
     * @param paths_ A map of file paths and item types.
     */
    explicit ShopDatabase(const std::map<std::string, ItemType> &paths_);

    /**

     * @brief Constructor for the ShopDatabase class that takes a file path and an item type.
     * Initializes the data members of the class and loads the data from the specified file.
     * @param path_ The file path.
     * @param item_type The item type.
     */
    explicit ShopDatabase(const std::string &path_, const ItemType &item_type);

    /**
     * @brief Destructor for the ShopDatabase class.
     * Saves the data to the files and releases the allocated memory.
     */
    ~ShopDatabase();

    /**
     * @brief Prints the contents of the database to the console.
     */
    void printDB() const;

    /**
     * @brief Saves the data to the files.
     */
    void saveData() noexcept;

    /**
     * @brief Deletes a record from the database.
     * @param item_type The item type.
     * @param index The index of the record in the vector.
     */
    void deleteRecord(const ItemType &item_type, int index);

    /**
     * @brief Deletes a record from the database by ID.
     * @param item_type The item type.
     * @param ID_ The ID of the record.
     */
    void deleteByID(const ItemType &item_type, long ID_);

    /**
     * @brief Overloaded operator for deleting a record from the database by ID.
     * @param pair_ A pair containing the item type and ID of the record.
     */
    ShopDatabase &operator-=(std::pair<ItemType, long> &pair_);

    /**
     * @brief Adds a new record to the database.
     * @param item_type The item type.
     * @param new_data A pointer to the new record.
     */
    void addRecord(const ItemType &item_type, Item *new_data);

    /**
     * @brief Adds a new record to the database.
     * @param item_type The item type.
     * @param str_data A string containing the data for the new record.
     */
    void addRecord(const ItemType &item_type, const std::string &str_data);

    /**
     * @brief Overloaded operator for adding a new record to the database.
     * @param pair_ A pair containing the item type and data for the new record.
    */
    ShopDatabase &operator+=(const std::pair<ItemType, std::string> &pair_);

    /**
     * @brief Overloaded operator for accessing a record by ID.
     * @param pair_ A pair containing the item type and ID of the record.
     */
    Item *operator[](const std::pair<ItemType, long> &pair_);

    /**
     * @brief Sorts the records in the database by a specified column.
     * @param item_type The item type.
     * @param column_name The name of the column to sort by.
     * @param ascending A flag indicating the sort order.
     */
    void sortBy(const ItemType &item_type, const std::string &column_name, bool ascending = true);

    /**
     * @brief Returns a reference to the map containing the records.
     * @return A reference to the map containing the records.
     */
    std::map<ItemType, std::vector<Item *>> &getItems();

    /**
     * @brief Returns the headers of a specific item type in the database.
     * @param item_type The item type.
     * @return A vector of strings containing the headers.
    */
    [[nodiscard]]std::vector<std::string> getHeaders(const ItemType &item_type) const noexcept;

    /**
     * @brief Helper function for creating a new object of the correct child class.
     * @param item_type The item type.
     * @return A pointer to the new object.
     */
    static Item *selectCorrectChild(const ItemType &) noexcept;

    /**
     * @brief Returns a vector of unique IDs for a specific item type in the database.
     * @param item_type The item type.
     * @return A vector of long integers containing the unique IDs.
     */
    [[nodiscard]]std::vector<long> getUniqueID(const ItemType &item_type) const;

private:
    /**
     * @brief Opens a file and loads the data into the database.
     * @param path The file path.
     * @param item_type The item type.
     */
    void open(const std::string &path, const ItemType &item_type);

    /**
     * @brief Saves the data for a specific item type to a file.
     * @param item_type The item type.
     */
    void save(const ItemType &item_type);

    /**
     * @brief Initializes the internal maps.
     */
    void initMap() noexcept;

    /**
     * @brief Helper function for converting an item type to a file path.
     * @param item_type The item type.
     * @return A string containing the file path.
     */
    static std::string itemTypeToPath(const ItemType &item_type) noexcept;

    /**
     * @brief Helper function for selecting the correct column names for a specific item type.
     * @param item_type The item type.
     * @return A string containing the column names.
     */
    static std::string selectCorrectColumnNames(const ItemType &item_type) noexcept;
};
/**
 * @brief Template function for printing the contents of a map.
 * @tparam K The type of the key in the map.
 * @tparam V The type of the value in the map.
 * @param m The map to be printed.
 */
template <typename K, typename V>
void printMap(const std::map<K, V> &m);