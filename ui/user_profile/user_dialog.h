/**
 * @file user_dialog.h
 * @author bartoszpiechnik25@gmail.com
 * @brief File containing the UserDialog class definition.
 * @version 0.1
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <QDialog>
#include "user.h"
#include "login.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UserDialog; }
QT_END_NAMESPACE

/**
 * @brief The UserDialog class
 * This class creates a dialog window for the user to change their password and add money to their account.
 */
class UserDialog : public QDialog {
Q_OBJECT
private:
    Ui::UserDialog *ui;
    User *user;
public:
    /**
     * @brief Construct a new User Dialog object
     * @param parent Pointer to the parent widget
     */
    explicit UserDialog(QWidget *parent = nullptr);

    /**
     * @brief Destroy the User Dialog object
     */
    ~UserDialog() override;

    /**
     * @brief Sets the user
     * @param user_ Pointer to the user
     */
    void initializeListView(User *user_);
private:
    /**
     * @brief Overriden close event handler
     * This function is called when the user closes the window. It emits the cancelClicked() signal.
     * @param event Pointer to the close event
     */
    void closeEvent(QCloseEvent *event) override;

public slots:

    /**
     * @brief Slot for the ok button
     * This slot is called when the user clicks the ok button.
     */
    void changePassword();

    /**
     * @brief Slot for the cancel button
     * This slot is called when the user clicks the cancel button.
     */
    void addMoney();
};