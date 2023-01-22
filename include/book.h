/**
 * @file book.h
 * @author your name (you@domain.com)
 * @brief This file contains the implementation of the Book class.
 * The Book class is a child class of Item, and provides additional properties for books
 *  such as author and type.
 * @version 1.0
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "item.h"

/**
 * @class Book
 * @brief The Book class is a child class of Item, and provides additional properties for books such as author and type.
 */
class Book final: public Item {
private:
    std::string author;
    std::string type;

    [[nodiscard]]bool isEmpty() const override;

public:
    /**
     * @brief Default constructor for the Book class. 
     * Initializes the data members of the class.
     */
    Book();

    /**
     * @brief Initializes the data members of the class with the provided values.
     * @param id_ The ID of the book.
     * @param name_ The name of the book.
     * @param description_ The description of the book.
     * @param price_ The price of the book.
     * @param author_ The author of the book.
     * @param type_ The type of the book.
     */
    Book(const long &id_, const std::string &name_, const std::string &description_, const double &price_,
         const std::string &author_,
         const std::string &type_);

    /**
     * @brief Initializes the data members of the class with the provided values.
     * @param id_ The ID of the book.
     * @param name_ The name of the book.
     * @param description_ The description of the book.
     * @param price_ The price of the book.
     * @param author_ The author of the book.@param type_ The type of the book.
     */
    Book(const long &id_, const char *name_, const char *description, const double &price_, const char *author_,
         const char *type_);

    /**
     * @brief Copy constructor for the Book class.
     * Initializes the data members of the class with the values from the other book.
     * @param other_book The other book.
     */
    Book(const Book &other_book);

    /**
     * @brief Destructor for the Book class.
     */
    ~Book() final;

    /**
     * @brief Sets the author of the book.
     * @param author_ The new author.
     */
    void setAuthor(const std::string &author_) noexcept;

    /**
     * @brief Sets the author of the book.
     * @param author_ The new author.
     */
    void setAuthor(const char *author_) noexcept;

    /**
     * @brief Sets the type of the book.
     * @param type_ The new author.
     */
    void setType(const char *type_) noexcept;

    /**
     * @brief Sets the type of the book.
     * @param type_ The new author.
     */
    void setType(const std::string &type) noexcept;

    /**
     * @brief Returns the author of the book. 
     * @return The author of the book.
     */
    [[nodiscard]]std::string getAuthor() const noexcept;

    /**
     * @brief Returns the type of the book.
     * @return The type of the book.
     */
    [[nodiscard]]std::string getType() const noexcept;

    /**
     * @brief Returns all properties of the item in a map.
     * @return A map containing all the properties of the item.
     */
    [[nodiscard]]std::map<std::string, std::string> getAll() const override;

    /**
     * @brief Sets all the properties of the item from a map.
     * @param data The map containing the properties of the item.
     */
    void setAll(std::map<std::string, std::string> &data) override;

    /**
     * @brief Reads the properties of the item from a string.
     * @param data The string containing the properties of the item.
     */
    void readFromStr(std::string &data) override;

    /**
     * @brief Saves the properties of the item to a string in the format for writing to a file.
     * @return A string containing the properties of the item.
     */
    std::string saveToDatabase() override;

    /**
     * @brief Check if the item contains the given string in any of its properties.
     * @param str The string to search for.
     * @return A boolean indicating if the item contains the given string.
     */
    bool contains(const std::string &str) override;
};