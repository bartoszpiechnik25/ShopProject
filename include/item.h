#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <limits>
#include <thread>
#include <map>
#include <regex>
#include <algorithm>
#include "exception.h"

class Item {
protected:
    long id;
    std::string name;
    std::string description;
    double price;

    [[nodiscard]]virtual bool isEmpty() const = 0;

public:
    Item();

    Item(const long &id_, const std::string &name_, const std::string &description_, const double &price_);

    Item(const long &id_, const char *name_, const char *description_, const double &price_);

    Item(const Item &other);

    virtual ~Item() = 0;

    void setID(const long &id_) noexcept;

    void setName(const std::string &name_) noexcept;

    void setName(const char *name_) noexcept;

    void setDescription(const std::string &description_) noexcept;

    void setDescription(const char *description_) noexcept;

    void setPrice(const double &price_) noexcept;

    [[nodiscard]]long getID() const noexcept;

    [[nodiscard]]std::string getName() const noexcept;

    [[nodiscard]]std::string getDescription() const noexcept;

    [[nodiscard]]double getPrice() const noexcept;

    [[nodiscard]]virtual std::map<std::string, std::string> getAll() const = 0;

    virtual void setAll(std::map<std::string, std::string> &data) = 0;

    virtual void readFromStr(std::string &) = 0;

    virtual std::string saveToDatabase() = 0;

    virtual bool contains(const std::string &str) = 0;
};