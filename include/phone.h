#pragma once

#include "item.h"

class Phone: public Item {
private:
    std::string manufacturer;
    std::string specs;
    bool isEmpty() const override;
public:
    Phone();
    Phone(const long&, const std::string&, const std::string&, const double&, const std::string&, const std::string&);
    Phone(const long&, const char*, const char*, const double&, const char*, const char*);
    Phone(const Phone&);
    ~Phone();
    void setModel(const std::string&);
    void setModel(const char*);
    void setManufacturer(const char*);
    void setManufacturer(const std::string&);
    void setSpecs(const char*);
    void setSpecs(const std::string&);
    std::string getModel() const;
    std::string getManufacturer() const;
    std::string getSpecs() const;
    std::map<std::string, std::string> getAll() const override;
    void setAll() override;
    void readFromStr(std::string&) override;
    std::string saveToDatabase() override;
};