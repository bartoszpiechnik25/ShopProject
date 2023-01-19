//
// Created by barto on 1/18/2023.
//

#ifndef SHOPPROJECTQT_USER_H
#define SHOPPROJECTQT_USER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

class User {
private:
    std::string username, password;
    std::vector<std::string> history;
    double credits;
public:
    explicit User();
    explicit User(const std::string& username, const std::string& passwd, double money);
    ~User() = default;
    void addCredits(double amount) noexcept;
    void subtractCredits(double amount) noexcept;
    void appendHistory(const std::string& bought_item) noexcept;
    [[nodiscard]] const std::vector<std::string>& getHistory() const noexcept;
    [[nodiscard]] const std::string& getUsername() const noexcept;
    [[nodiscard]] const std::string& getPassword() const noexcept;
    [[nodiscard]] const double getMoney() const noexcept;
    void setPassword(const std::string& passwd) noexcept;
    void saveToBinary(std::ofstream& file);
    void readFromBinary(std::ifstream& file);
};

#endif //SHOPPROJECTQT_USER_H
