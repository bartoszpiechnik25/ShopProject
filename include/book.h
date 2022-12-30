#pragma once
#include "item.h"
#include "exception.h"

class Book: public Item {
private:
    std::string author;
    std::string type;
    bool isEmpty() const override;
public:
    Book();
    Book(const long&, const std::string&, const std::string&, const double&, const std::string&, const std::string&);
    Book(const long&, const char*, const char*, const double&, const char*, const char*);
    Book(const Book&);
    ~Book();
    void setAuthor(const std::string&);
    void setAuthor(const char*);
    void setType(const char*);
    void setType(const std::string&);
    std::string getAuthor() const;
    std::string getType() const;
    std::map<std::string, std::string> getAll() const override;
    void setAll() override;
    void readFromStr(std::stringstream&) override;
    std::stringstream saveToDatabase() override;
};

template <typename T>
T readNumericValue(const char*);
std::string readString(const char*);
