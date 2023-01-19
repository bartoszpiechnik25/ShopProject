//
// Created by barto on 1/18/2023.
//
#include "user.h"

User::User() {}

User::User(const std::string &username, const std::string &passwd, const double money):
        username(username), password(passwd), credits(money) {}

void User::addCredits(const double amount) noexcept {
    credits += amount;
}

void User::subtractCredits(const double amount) noexcept {
    credits -= amount;
}

void User::appendHistory(const std::string &bought_item) noexcept {
    history.push_back(bought_item);
}

const std::string& User::getUsername() const noexcept {
    return username;
}

const std::string& User::getPassword() const noexcept {
    return password;
}

const std::vector<std::string>& User::getHistory() const noexcept {
    return history;
}

double User::getMoney() const noexcept {
    return credits;
}

void User::setPassword(const std::string &passwd) noexcept {
    this->password = passwd;
}

void User::saveToBinary(std::ofstream &file) {
    if (file.good()) {
        std::size_t username_size = username.size(), passwd_size = password.size(), history_size = history.size();
        file.write(reinterpret_cast<char *>(&username_size), sizeof(username_size));
        file.write(&username[0], username_size);
        file.write(reinterpret_cast<char *>(&passwd_size), sizeof(passwd_size));
        file.write(&password[0], passwd_size);
        file.write(reinterpret_cast<char *>(&history_size), sizeof(history_size));
        for (const auto &element: history) {
            std::size_t element_size = element.size();
            file.write(reinterpret_cast<char *>(&element_size), sizeof(element_size));
            file.write(&element[0], element_size);
        }
        file.write(reinterpret_cast<char *>(&credits), sizeof(credits));
    } else throw std::runtime_error("Error saving to file!");
}

void User::readFromBinary(std::ifstream &file) {
    if (file.good()) {
        std::size_t username_size, passwd_size, history_size;
        file.read(reinterpret_cast<char *>(&username_size), sizeof(username_size));
        username.resize(username_size);
        file.read(&username[0], username_size);
        file.read(reinterpret_cast<char *>(&passwd_size), sizeof(passwd_size));
        password.resize(passwd_size);
        file.read(&password[0], passwd_size);
        file.read(reinterpret_cast<char *>(&history_size), sizeof(history_size));
        for (int i = 0; i < history_size; ++i) {
            std::string tmp;
            std::size_t tmp_size;
            file.read(reinterpret_cast<char *>(&tmp_size), sizeof(tmp_size));
            tmp.resize(tmp_size);
            file.read(&tmp[0], tmp_size);
            history.push_back(tmp);
        }
        file.read(reinterpret_cast<char *>(&credits), sizeof(credits));
    } else throw std::runtime_error("Error while reading user from file!");
}

