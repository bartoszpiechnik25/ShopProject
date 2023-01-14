//
// Created by barto on 1/9/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Login.h" resolved

#include "login.h"
#include "ui_Login.h"

/**
 * @brief Constructor of Login class
 * @param parent - parent widget
 */
Login::Login(QWidget *parent) :
        QDialog(parent), ui(new Ui::Login) {
    std::thread load_database_thread(&Login::loadUsersDatabase, this);
    load_database_thread.join();
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->okButton->setDefault(false);
    ui->cancelButton->setDefault(false);
    ui->usernameLineEdit->setFocus();
    this->setFixedSize(this->size());
    connect(ui->passwordLineEdit, SIGNAL(returnPressed()), this, SLOT(enteredPasswd()));
    connect(ui->addUserButton, SIGNAL(clicked()), this, SLOT(addUser()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(enteredPasswd()));
    show();
}

/**
 * @brief Get username from line edit
 * @return std::string - username
 */
std::string Login::getUsername() const {
    return ui->usernameLineEdit->text().toStdString();
}

/**
 * @brief Get password from line edit
 * @return std::string - password
 */
std::string Login::getPasswd() const {
    return ui->passwordLineEdit->text().toStdString();
}

/**
 * @brief Slot handling login to the shop
 */
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
        std::string username = getUsername();
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
        emit loginSuccessful(username);
    }
}

Login::~Login() {
    delete ui;
}

/**
 * @brief Create custom message box with given parameters.
 * @param title - title of the message box
 * @param text - text of the message box
 * @param icon - icon of the message box
 * @param buttons - buttons of the message box
 */
void Login::createMessageBox(const char *title, const char *text, QMessageBox::Icon icon,
                             QMessageBox::StandardButtons buttons) {
    QMessageBox messageBox;
    messageBox.setStyleSheet("color: white; background-color: rgb(105,105,105); QPushButton {background-color: rgb(67,70,75); border-width: 2px; border-radius: 10px; border-color: beige; font: bold 12px; color: white; padding: 5px;} QPushButton:pressed {border-style: inset;border: 2px solid #add8e6;}");
    messageBox.setWindowTitle(title);
    messageBox.setText(text);
    messageBox.setIcon(icon);
    messageBox.setStandardButtons(buttons);
    messageBox.exec();
}

/**
 * @brief Load users database from file
 */
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

/**
 * @brief Write users database to file
 */
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

/**
 * @brief Slot handling adding new user to the database
 */
void Login::addUser() {
    if (getUsername().empty() || getPasswd().empty()) {
        createMessageBox("Warning", "Cannot add empty!", QMessageBox::Warning, QMessageBox::Ok | QMessageBox::NoButton);
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

/**
 * @brief Slot handling cancel button
 */
void Login::cancelClicked() {
    this->close();
}

/**
 * @brief Handling closing the window
 * @param event - close event
 */
void Login::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter && ui->passwordLineEdit->hasFocus()) {
        ui->passwordLineEdit->setFocus();
    } else QDialog::keyPressEvent(event);
}


