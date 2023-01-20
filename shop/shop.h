//
// Created by barto on 1/10/2023.
//

#ifndef SHOPPROJECTQT_SHOP_H
#define SHOPPROJECTQT_SHOP_H

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

class Shop : public QMainWindow {
Q_OBJECT
private:
    Ui::Shop *ui;
    ShopDatabase *database;
    QTableWidget *phones, *books;
    Login *m_login;
    SellDialog *sellDialog;
    SellBookDialog *sellBookDialog;
    SortWindow *sortWindow;
    QAction *resetMenubar, *menuProfile;
    std::map<std::string, User> usersDatabase;
    UserDialog *userDialog;
    std::string currentUser;
public:
    explicit Shop(QWidget *parent = nullptr);

    ~Shop() override;

    void closeEvent(QCloseEvent *event) override;

private:
    void initializeUi();

    void initializeTab();

    void initializeTable(const ItemType &item_type, QTableWidget *tableWidget);

    void connectSlots() noexcept;

    void initializePointers() noexcept;

public slots:

    void loginSuccessful(const std::string &username, std::map<std::string, User> &usersDatabase_);

    void sellButtonClicked();

    void addNewItem(std::map<std::string, std::string> &data);

    void sortData(const std::string &column, bool ascending);

    void createSortWindow();

    void buyButtonClicked();

    void searchForData();

    void resetClicked();

    void profileClicked();
};

#endif //SHOPPROJECTQT_SHOP_H
