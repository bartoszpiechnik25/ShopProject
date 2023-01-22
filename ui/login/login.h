/**
 * @file login.h
 * @author bartoszpiechnik25@gmail.com
 * @brief 
 * @version 1.0
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <QDialog>
#include <QMessageBox>
#include <map>
#include <string>
#include <thread>
#include <fstream>
#include <iostream>
#include <QCloseEvent>
#include "user.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

/**
 * @class Login
 * @brief Handles user login and registration
 * This class creates a login dialog for the user to enter their credentials and also allows for new user registration.
 * It also handles loading and saving the user database from a file.
 */
class Login : public QDialog {
Q_OBJECT
private:
    Ui::Login *ui;
    std::map<std::string, User> usersDatabase;
public:
    /**
     * @brief onstructor for the Login class
     * This constructor initializes the user interface and loads the user database from a file.
     * @param parent Pointer to the parent widget
     */
    explicit Login(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Login object
     */
    ~Login() override;

    /**
     * @brief Getter for the entered username
     * @return std::string The username entered by the user
     */
    [[nodiscard]]std::string getUsername() const noexcept;

    /**
     * @brief Getter for the entered password
     * @return std::string The password entered by the user
     */
    [[nodiscard]]std::string getPasswd() const noexcept;

    /**
     * @brief Creates a message box with the given parameters
     * This function is a static function that creates a message box with the given title, text, icon, and buttons.
     * @param title Title of the message box
     * @param text Text of the message box
     * @param icon Icon of the message box
     * @param buttons Buttons of the message box
     */
    static void
    createMessageBox(const char *title, const char *text, QMessageBox::Icon icon, QMessageBox::StandardButtons buttons);

    /**
     * @brief Fill line edits with data from programme arguments.
     */
    void loginFromArgs();

public slots:
    /**
     * @brief Slot for the login button
     */
    void enteredPasswd();

    /**
     * @brief Slot for the Add user button
     */
    void addUser();
    
    /**
     * @brief Slot for the Cancel button
     */
    void cancelClicked();

signals:
    /**
     * @brief Signal emitted when the user successfully logs in
     * @param username std::string The username of the user
     * @param database std::map<std::string, User> The users database
     */
    void loginSuccessful(const std::string &username, std::map<std::string, User> &database);

private:
    /**
     * @brief Helper funtion loading the users database from a file
     */
    void loadUsersDatabase();

    /**
     * @brief Helper function saving the users database to a file
     */
    void writeUsersDatabase();

protected:
    /**
     * @brief Overridden close event handler
     * This function overrides the default close event handler and emits the loginSuccessful signal with the username and
     * users database.
     * @param event Pointer to the close event
     */
    void keyPressEvent(QKeyEvent *event) override;
};