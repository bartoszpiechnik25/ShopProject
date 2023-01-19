#pragma once
#include "item.h"

class Book final: public Item {
private:
    std::string author;
    std::string type;

    [[nodiscard]]bool isEmpty() const override;

public:
    Book();

    Book(const long &id_, const std::string &name_, const std::string &description_, const double &price_, const std::string &author_,
         const std::string & type_);

    Book(const long &id_, const char *name_, const char *description, const double &price_, const char *author_, const char *type_);

    Book(const Book &other_book);

    ~Book() final;

    void setAuthor(const std::string &author_) noexcept;

    void setAuthor(const char *author_) noexcept;

    void setType(const char *type_) noexcept;

    void setType(const std::string &type) noexcept;

    [[nodiscard]]std::string getAuthor() const noexcept;

    [[nodiscard]]std::string getType() const noexcept;

    [[nodiscard]]std::map<std::string, std::string> getAll() const override;

    void setAll(std::map<std::string, std::string> &data) override;

    void readFromStr(std::string &data) override;

    std::string saveToDatabase() override;

    bool contains(const std::string &str) override;
};