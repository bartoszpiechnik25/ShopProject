/**
 * @file book.h
 * @author bartoszpiechnik25@gmail.com
 * @brief This file contains the implementation of the Shop class.
 * @version 1.0
 * @date 2023-01-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <QMainWindow>
#include <QStyleFactory>
#include <QLabel>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QHeaderView>
#include <algorithm>
#include "database.h"
#include "login.h"
#include "selldialog.h"
#include "sellbookdialog.h"
#include "sortwindow.h"
#include "user_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Shop; }
QT_END_NAMESPACE

/**
 * @class Shop
 * @brief The main window class of the application.
 * The Shop class is the main window class of the application, it is responsible for displaying the main window,
 *  creating and displaying the other windows, and handling the interactions between them.
 */
class Shop : public QMainWindow {
Q_OBJECT
private:
    Ui::Shop *ui;
    ShopDatabase *database;
    QTableWidget *phones, *books, *sorted;
    Login *m_login;
    SellDialog *sellDialog;
    SellBookDialog *sellBookDialog;
    SortWindow *sortWindow;
    QAction *resetMenubar, *menuProfile, *dbInfo;
    std::map<std::string, User> usersDatabase;
    UserDialog *userDialog;
    std::string currentUser;
public:
    /**
     * @brief Constructor for the Shop class.
     * @param parent The parent widget of the Shop class.
     */
    explicit Shop(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Shop class.
     */
    ~Shop() override;

    /**
     * @brief Event handler for the close event.
     * @param event The close event.
     */
    void closeEvent(QCloseEvent *event) override;

private:
    /**
     * @brief Initializes the tabs of the main window.
    */
    void initializeUi();

    /**
     * @brief Initializes the table widget for the specified item type.
     * @param item_type The type of item for which the table widget will be initialized.
     * @param tableWidget The table widget that will be initialized.
     */
    void initializeTab();

    /**
     * @brief Connects the slots of the main window.
     */
    void initializeTable(const ItemType &item_type, QTableWidget *tableWidget);

    /**
     * @brief Initializes the pointers of the main window.
     */
    void connectSlots() noexcept;

    /**
     * @brief Initializes the pointers of the main window.
     */
    void initializePointers() noexcept;

public slots:

    /**
     * @brief Slot that is called when a user successfully logs in.
     * @param username The username of the logged in user.
     * @param usersDatabase_ The map of users in the application.
     */
    void loginSuccessful(const std::string &username, std::map<std::string, User> &usersDatabase_);

    /**
     * @brief Slot that is called when the sell button is clicked.
     */
    void sellButtonClicked();

    /**
     * @brief Slot that is called when a new item is added to the database.
     * @param data The data of the new item.
     */
    void addNewItem(std::map<std::string, std::string> &data);

    /**
     * @brief Slot that is called when the data is sorted.
     * @param column The column by which the data will be sorted.
     * @param ascending A boolean indicating if the data will be sorted in ascending or descending order.
     */
    void sortData(const std::string &column, bool ascending);

    /**
     * @brief Slot that is called when the sort window is created.
     */
    void createSortWindow();

    /**
     * @brief Slot that is called when the buy button is clicked.
     */
    void buyButtonClicked();

    /**
     * @brief Slot that is called when a search is performed.
     */
    void searchForData();

    /**
     * @brief Slot that is called when the reset button is clicked.
     */
    void resetClicked();

    /**
     * @brief Slot that is called when the profile button is clicked.
     */
    void profileClicked();

    /**
     * @brief Slot that is called when the database info button is clicked.
     */
    void printDBInfo();
};