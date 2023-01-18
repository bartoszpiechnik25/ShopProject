//
// Created by barto on 1/10/2023.
//

#ifndef SHOPPROJECTQT_SHOP_H
#define SHOPPROJECTQT_SHOP_H

#include <QMainWindow>
#include <QStyleFactory>
#include <QTableWidget>
#include <QHeaderView>
#include "database.h"
#include "login.h"
#include "selldialog.h"
#include "sellbookdialog.h"
#include "sortwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Shop; }
QT_END_NAMESPACE

class Shop : public QMainWindow {
Q_OBJECT

public:
    explicit Shop(QWidget *parent = nullptr);
    ~Shop() override;
    void closeEvent(QCloseEvent* event) override;
private:
    void initializeUi();
    void initializeTab();
    void initializeTable(const ItemType& item_type, QTableWidget* tableWidget);
private:
    Ui::Shop *ui;
    ShopDatabase* database;
    QTableWidget* phones, *books;
    Login* m_login;
    SellDialog* sellDialog;
    SellBookDialog* sellBookDialog;
    SortWindow* sortWindow;
public slots:
    void loginSuccessful(const std::string& username);
    void cellActivated(int row, int column);
    void sellButtonClicked();
    void addNewItem(std::map<std::string, std::string>& data);
    void sortData(const std::string& column, bool ascending);
    void createSortWindow();
    void buyButtonClicked();
    signals:
    void uniqueIDs(std::vector<long>& ID_);
};

#endif //SHOPPROJECTQT_SHOP_H
