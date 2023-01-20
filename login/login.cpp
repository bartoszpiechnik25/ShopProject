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
    loginFromArgs();
    show();
    load_database_thread.join();
}

/**
 * @brief Get username from line edit
 * @return std::string - username
 */
std::string Login::getUsername() const noexcept{
    return ui->usernameLineEdit->text().toStdString();
}

/**
 * @brief Get password from line edit
 * @return std::string - password
 */
std::string Login::getPasswd() const noexcept{
    return ui->passwordLineEdit->text().toStdString();
}

/**
 * @brief Slot handling login to the shop
 */
void Login::enteredPasswd() {
    if (!usersDatabase.contains(getUsername())) {
        createMessageBox("Warning", "User not found", QMessageBox::Warning,
                         QMessageBox::Ok | QMessageBox::NoButton);
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
    } else if (usersDatabase[getUsername()].getPassword() != getPasswd()) {
        createMessageBox("Warning", "Wrong password", QMessageBox::Warning,
                         QMessageBox::Ok | QMessageBox::NoButton);
        ui->passwordLineEdit->clear();
    } else {
        std::string username = getUsername();
        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
        std::cout << "bedzie emit?" << std::endl;
        emit loginSuccessful(username, usersDatabase);
//        this->close();
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
    messageBox.setStyleSheet(
            "color: white; background-color: rgb(105,105,105); QPushButton {background-color: rgb(67,70,75); border-width: 2px; border-radius: 10px; border-color: beige; font: bold 12px; color: white; padding: 5px;} QPushButton:pressed {border-style: inset;border: 2px solid #add8e6;}");
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
    std::ifstream database{"../data/users.bin", std::ios::binary};
    while (database.peek() != EOF) {
        try {
            User tmp;
            tmp.readFromBinary(database);
            usersDatabase[tmp.getUsername()] = tmp;
        } catch (const std::runtime_error &err) {
            Login::createMessageBox("Critical", err.what(), QMessageBox::Critical,
                                    QMessageBox::Ok | QMessageBox::NoButton);
            std::terminate();
        }

    }
    database.close();
}

/**
 * @brief Write users database to file
 */
void Login::writeUsersDatabase() {
    std::ofstream database{"../data/users.bin", std::ios::binary};
    for (auto &[id, user]: usersDatabase) {
        try {
            user.saveToBinary(database);
        } catch (const std::runtime_error &err) {
            Login::createMessageBox("Critical", err.what(), QMessageBox::Critical,
                                    QMessageBox::Ok | QMessageBox::NoButton);
        }
    }
    database.close();
}

/**
 * @brief Slot handling adding new user to the database
 */
void Login::addUser() {
    std::string username = getUsername(), passwd = getPasswd();
    if (username.empty() || passwd.empty()) {
        createMessageBox("Warning", "Cannot add empty!", QMessageBox::Warning,
                         QMessageBox::Ok | QMessageBox::NoButton);
    } else if (username.ends_with(' ') || username.starts_with(' ') || passwd.starts_with(' ') ||
               passwd.ends_with(' ')) {
        createMessageBox("Warning", "Username cannot start/end with a space!", QMessageBox::Critical,
                         QMessageBox::Ok | QMessageBox::NoButton);
        ui->passwordLineEdit->clear();
        ui->usernameLineEdit->clear();
    } else {
        if (usersDatabase.contains(username)) {
            createMessageBox("Warning", "User already exists", QMessageBox::Warning,
                             QMessageBox::Ok | QMessageBox::NoButton);
        } else {
            usersDatabase[username] = User(username, getPasswd(), 0.0);
            writeUsersDatabase();
            createMessageBox("Information", "User added successfully", QMessageBox::Information,
                             QMessageBox::Ok | QMessageBox::NoButton);
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

/**
 * @brief Login user by values passed as arguments, if data is correct else shows login window.
 */
void Login::loginFromArgs() {
    QStringList args = QCoreApplication::arguments();
    if (args.size() == 3) {
        ui->usernameLineEdit->setText(args[1]);
        ui->passwordLineEdit->setText(args[2]);
        ui->okButton->setFocus();
    }
}


