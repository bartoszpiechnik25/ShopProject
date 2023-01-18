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
    Item(const long&, const std::string&, const std::string&, const double&);
    Item(const long&, const char*, const char*, const double&);
    Item(const Item&);
    virtual ~Item() = 0;
    void setID(const long&);
    void setName(const std::string&);
    void setName(const char*);
    void setDescription(const std::string&);
    void setDescription(const char*);
    void setPrice(const double&);
    [[nodiscard]]long getID() const;
    [[nodiscard]]std::string getName() const;
    [[nodiscard]]std::string getDescription() const;
    [[nodiscard]]double getPrice() const;
    [[nodiscard]]virtual std::map<std::string, std::string> getAll() const = 0;
    virtual void setAll(std::map<std::string, std::string>&) = 0;
    virtual void readFromStr(std::string&) = 0;
    virtual std::string saveToDatabase() = 0;
    virtual bool contains(const std::string& str) = 0;
    static long readLongValue(const char*);
    static double readDoubleValue(const char*);
    static std::string readString(const char*);
};