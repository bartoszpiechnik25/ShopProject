//
// Created by barto on 1/10/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Shop.h" resolved

#include "shop.h"
#include "ui_Shop.h"


Shop::Shop(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::Shop) {
    initializeUi();
    m_login = new Login();
    std::map<std::string, ItemType> paths = {{"../data/phones_database.csv", PHONES}, {"../data/books_database.csv", BOOKS}};
    database = new ShopDatabase(paths);
    books = new QTableWidget(this);
    books->setEditTriggers(QAbstractItemView::NoEditTriggers);
    phones = new QTableWidget(this);
    phones->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sellDialog = new SellDialog();
    sellBookDialog = new SellBookDialog();
    sortWindow = new SortWindow();
    initializeTab();
    connect(m_login, &Login::loginSuccessful, this, &Shop::loginSuccessful);
    connect(ui->sellButton, SIGNAL(clicked()), this, SLOT(sellButtonClicked()));
    connect(sellDialog, &SellDialog::sendData, this, &Shop::addNewItem);
    connect(ui->sortByButton, SIGNAL(clicked()), this, SLOT(createSortWindow()));
    connect(sortWindow, &SortWindow::sortDataBy, this, &Shop::sortData);
    connect(ui->buyButton, SIGNAL(clicked()), this, SLOT(buyButtonClicked()));
}

Shop::~Shop() {
    delete ui;
    delete m_login;
    delete sellDialog;
    delete sellBookDialog;
    delete database;
    delete phones;
    delete books;
}

void Shop::loginSuccessful(const std::string &username) {
    m_login->close();
    if (username == "admin")
        Login::createMessageBox("Information", "Admin login successful", QMessageBox::Information, QMessageBox::Ok | QMessageBox::NoButton);
    std::string statusBarHelloMessage = username + " welcome to the shop!";
    ui->statusbar->showMessage(statusBarHelloMessage.c_str());
    show();
}

void Shop::cellActivated(int row, int column) {
    Login::createMessageBox("Information", "Cell activated", QMessageBox::Information, QMessageBox::Ok | QMessageBox::NoButton);
    std::cout << row << " " << column << std::endl;
}

void Shop::sellButtonClicked() {
    std::vector<long> uniqueIDs;
    if (ui->tabWidget->currentWidget() == phones) {
         uniqueIDs = database->getUniqueID(PHONES);
        sellDialog->setID(uniqueIDs);
        sellDialog->show();
    }
    else {
        uniqueIDs = database->getUniqueID(BOOKS);
        sellBookDialog->setID(uniqueIDs);
        sellBookDialog->show();
    }
}

void Shop::addNewItem(std::map<std::string, std::string>& data) {
    if (data.empty())
        return;
    ItemType item_type;
    QTableWidget* tableWidget;

    if (ui->tabWidget->currentWidget() == phones) {
        item_type = PHONES;
        tableWidget = phones;
    } else {
        item_type = BOOKS;
        tableWidget = books;
    }

    Item* new_item= ShopDatabase::selectCorrectChild(item_type);
    new_item->setAll(data);
    database->addRecord(item_type, new_item);
    tableWidget->setRowCount(tableWidget->rowCount() + 1);

    int row_count = phones->rowCount() - 1, counter = 0;
    for(const auto& column_name: database->getHeaders(item_type))
        tableWidget->setItem(row_count, counter++, new QTableWidgetItem(data[column_name].c_str()));
    tableWidget->repaint();
}

void Shop::initializeUi() {
    ui->setupUi(this);
    ui->statusbar->setStyleSheet("QStatusBar { color: white; font: 13px;}");
    ui->sortByButton->setStatusTip("Create new window with sorting properties");
    ui->sellButton->setStatusTip("Create new item to be sold");
    ui->buyButton->setStatusTip("Buy selected item from table");
    ui->searchLineEdit->setPlaceholderText("Search...");
}

void Shop::initializeTab() {
    initializeTable(PHONES, phones);
    ui->tabWidget->addTab(phones, "Phones");

    initializeTable(BOOKS, books);
    ui->tabWidget->addTab(books, "Books");
}

void Shop::initializeTable(const ItemType &item_type, QTableWidget* tableWidget) {
    std::map<ItemType, std::vector<Item*>>& items = database->getItems();
    tableWidget->setStyleSheet("QTableWidget { background-color: #171717; color: #FFFDE4; font: 12px; }  QHeaderView::section { border-radius: 10px; background-color: #171717; color: #FFFDE4; font: 12px; }");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView { background-color: #171717; color: #FFFDE4; font: 12px; }");
    tableWidget->verticalHeader()->setStyleSheet("QHeaderView { background-color: #171717; color: #FFFDE4; font: 12px; }");
    tableWidget->verticalHeader()->setVisible(false);
    QStringList list = QStringList();
    std::vector<std::string> headers = database->getHeaders(item_type);
    std::for_each(headers.begin(), headers.end(), [&list](const auto& header) { list << header.c_str(); });

    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels(list);
    tableWidget->setRowCount(items[item_type].size());
    int counter = 0;
    for(auto item: items[item_type]) {
        std::map<std::string, std::string> itemData = item->getAll();
        int i = 0;
        for(const auto& header: headers)
            tableWidget->setItem(counter, i++, new QTableWidgetItem(itemData[header].c_str()));
        counter++;
    }
    tableWidget->resizeColumnsToContents();
}

void Shop::closeEvent(QCloseEvent *event) {
    int result = QMessageBox::warning(this, "Confirm exit", "Are you sure you want to quit?", QMessageBox::Ok | QMessageBox::Cancel);
    if (result == QMessageBox::Ok) {
        database->saveData();
        event->accept();
    } else
        event->ignore();
}

void Shop::sortData(const std::string& column, bool ascending) {
    if (ui->tabWidget->currentWidget() == phones) {
        phones->clearContents();
        database->sortBy(PHONES, column, ascending);
        initializeTable(PHONES, phones);
    } else {
        books->clearContents();
        database->sortBy(BOOKS, column, ascending);
        initializeTable(BOOKS, books);
    }
}

void Shop::createSortWindow() {
    if (ui->tabWidget->currentWidget() == phones)
        sortWindow->setComboBoxData({"ID", "Price", "Name", "Manufacturer"});
    else
        sortWindow->setComboBoxData({"ID", "Price", "Name", "Type"});
    sortWindow->show();
}

void Shop::buyButtonClicked() {
    ItemType item_type;
    QTableWidget *tableWidget;

    if (ui->tabWidget->currentWidget() == phones) {
        item_type = PHONES;
        tableWidget = phones;
    } else {
        item_type = BOOKS;
        tableWidget = books;
    }

    int row = tableWidget->currentRow();
    if (row == -1) {
        Login::createMessageBox("Error", "To buy an item select valid row!", QMessageBox::Critical,
                                QMessageBox::Ok | QMessageBox::NoButton);
        return;
    }
    std::pair<ItemType, long> pair(item_type, tableWidget->item(row, 0)->text().toLong());
    *database -= pair;
    std::string soldItem = "Thank you for buying:\n";
    int counter = 0;
    for (const auto &header: database->getHeaders(item_type)) {
        soldItem += header + ": \t" + tableWidget->item(row, counter++)->text().toStdString() + "\n";
    }
    tableWidget->removeRow(row);
    tableWidget->update();
    tableWidget->setCurrentCell(-1, -1);
    Login::createMessageBox("Information", soldItem.c_str(), QMessageBox::Information,
                            QMessageBox::Ok | QMessageBox::NoButton);
}
