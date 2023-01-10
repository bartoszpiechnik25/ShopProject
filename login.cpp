//
// Created by barto on 1/9/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Login.h" resolved

#include "login.h"
#include "ui_Login.h"


Login::Login(QWidget *parent) :
        QDialog(parent), ui(new Ui::Login) {
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    this->setFixedSize(this->size());
    loadUsersDatabase();
    for(auto& user: usersDatabase) {
        std::cout << user.first << " " << user.second << std::endl;
    }
    connect(ui->usernameLineEdit, SIGNAL(returnPressed()), this, SLOT(enteredUsername()));
    connect(ui->passwordLineEdit, SIGNAL(returnPressed()), this, SLOT(enteredPasswd()));
    connect(ui->addUserButton, SIGNAL(clicked()), this, SLOT(addUser()));
    show();
}

std::string Login::getUsername() const {
    return ui->usernameLineEdit->text().toStdString();
}

std::string Login::getPasswd() const {
    return ui->passwordLineEdit->text().toStdString();
}

void Login::enteredUsername() {
    if (!usersDatabase.contains(getUsername())) {
        createMessageBox("Warning", "User not found", QMessageBox::Warning, QMessageBox::Ok | QMessageBox::NoButton);
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
    }
}

void Login::enteredPasswd() {
    if (!usersDatabase.contains(getUsername())) {
        createMessageBox("Warning", "User not found", QMessageBox::Warning, QMessageBox::Ok | QMessageBox::NoButton);
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
    }
    else if (usersDatabase[getUsername()] != getPasswd()) {
        createMessageBox("Warning", "Wrong password", QMessageBox::Warning, QMessageBox::Ok | QMessageBox::NoButton);
        ui->passwordLineEdit->clear();
    }
    else {
        createMessageBox("Information", "Login successful", QMessageBox::Information, QMessageBox::Ok | QMessageBox::NoButton);
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
    }
}

Login::~Login() {
    delete ui;
}

void Login::createMessageBox(const char *title, const char *text, QMessageBox::Icon icon,
                             QMessageBox::StandardButtons buttons) {
    QMessageBox messageBox;
    messageBox.setWindowTitle(title);
    messageBox.setText(text);
    messageBox.setIcon(icon);
    messageBox.setStandardButtons(buttons);
    messageBox.exec();
}

void Login::loadUsersDatabase() {
    std::ifstream database{"../data/users_database.txt", std::ios::binary};
    size_t username_size, passwd_size;
    std::string username, passwd;
    if (database.good()) {
        while (!database.eof()) {
            database.read(reinterpret_cast<char *>(&username_size), sizeof(size_t));
            username.resize(username_size);
            database.read(&username[0], username_size);
            database.read(reinterpret_cast<char *>(&passwd_size), sizeof(size_t));
            passwd.resize(passwd_size);
            database.read(&passwd[0], passwd_size);
            usersDatabase[username] = passwd;
        }
    } else throw std::runtime_error("Error reading users database file");
    database.close();
}

void Login::writeUsersDatabase() {
    std::ofstream database{"../data/users_database.txt", std::ios::binary};
    size_t username_size, passwd_size;
    if (database.is_open()) {
        for (auto &[user, passwd]: usersDatabase) {
            username_size = user.size();
            passwd_size = passwd.size();
            database.write(reinterpret_cast<char*>(&username_size), sizeof(size_t));
            database.write(&user[0], username_size);
            database.write(reinterpret_cast<char*>(&passwd_size), sizeof(size_t));
            database.write(&passwd[0], passwd_size);
        }
        database.close();
    } else throw std::runtime_error("Cannot access database file for saving data");
}

void Login::addUser() {
    if (getUsername().empty() || getPasswd().empty()) {
        createMessageBox("Warning", "Username or password cannot be empty to add new user", QMessageBox::Warning, QMessageBox::Ok | QMessageBox::NoButton);
    } else {
        std::string username = getUsername();
        if (usersDatabase.contains(username)) {
            createMessageBox("Warning", "User already exists", QMessageBox::Warning, QMessageBox::Ok | QMessageBox::NoButton);
        } else {
            std::string passwd = getPasswd();
            usersDatabase[username] = passwd;
            writeUsersDatabase();
            createMessageBox("Information", "User added successfully", QMessageBox::Information, QMessageBox::Ok | QMessageBox::NoButton);
        }
    }
}


