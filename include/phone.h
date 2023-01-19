#pragma once

#include "item.h"

class Phone final: public Item {
private:
    std::string manufacturer;
    std::string specs;

    [[nodiscard]]bool isEmpty() const override;

public:
    Phone();

    Phone(const long &id_, const std::string &name_, const std::string &description_, const double &price_,
          const std::string &manufacturer_,
          const std::string &specs_);

    Phone(const long &id_, const char *name_, const char *description_, const double &price_, const char *manufacturer_,
          const char *specs_);

    Phone(const Phone &phone);

    ~Phone() final;

    void setManufacturer(const char *manufacturer_) noexcept;

    void setManufacturer(const std::string &manufacturer_) noexcept;

    void setSpecs(const char *specs_) noexcept;

    void setSpecs(const std::string &specs_) noexcept;

    [[nodiscard]]std::string getManufacturer() const noexcept;

    [[nodiscard]]std::string getSpecs() const noexcept;

    [[nodiscard]]std::map<std::string, std::string> getAll() const override;

    void setAll(std::map<std::string, std::string> &) override;

    void readFromStr(std::string &) override;

    bool contains(const std::string &str) override;

    std::string saveToDatabase() override;
};