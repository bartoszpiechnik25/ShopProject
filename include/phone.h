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
    [[nodiscard]]std::string getModel() const;
    [[nodiscard]]std::string getManufacturer() const;
    [[nodiscard]]std::string getSpecs() const;
    [[nodiscard]]std::map<std::string, std::string> getAll() const override;
    void setAll(std::map<std::string, std::string>&) override;
    void readFromStr(std::string&) override;
    bool contains(const std::string& str) override;
    std::string saveToDatabase() override;
};