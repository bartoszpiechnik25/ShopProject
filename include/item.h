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
#include <algorithm>
#include "exception.h"

class Item {
protected:
    long id;
    std::string name;
    std::string description;
    double price;
    virtual bool isEmpty() const = 0;
public:
    Item();
    Item(const long&, const std::string&, const std::string&, const double&);
    Item(const long&, const char*, const char*, const double&);
    Item(const Item&);
    virtual ~Item();
    //Setters
    void setID(const long&);
    void setName(const std::string&);
    void setName(const char*);
    void setDescription(const std::string&);
    void setDescription(const char*);
    void setPrice(const double&);
    //Getters
    long getID() const;
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    //Pure virtual functions
    virtual std::map<std::string, std::string> getAll() const = 0;
    virtual void setAll() = 0;
    virtual void readFromStr(std::string&) = 0;
    virtual std::string saveToDatabase() = 0;
    static long readLongValue(const char*);
    static double readDoubleValue(const char*);
    static std::string readString(const char*);
};