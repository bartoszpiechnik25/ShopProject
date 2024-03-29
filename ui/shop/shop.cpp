//
// Created by barto on 1/10/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Shop.h" resolved

#include "shop.h"
#include "ui_Shop.h"

Shop::Shop(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::Shop) {
    initializeUi();
    std::map<std::string, ItemType> paths = {{"../data/phones_database.csv", PHONES},
                                             {"../data/books_database.csv",  BOOKS}};

    try {
        database = new ShopDatabase(paths);
    } catch (const std::exception &e) {
        Login::createMessageBox("Error", e.what(), QMessageBox::Critical,
                                QMessageBox::Ok | QMessageBox::NoButton);
        exit(1);
    }
    initializePointers();
    initializeTab();
    connectSlots();
}

Shop::~Shop() {
    delete dbInfo;
    delete userDialog;
    delete resetMenubar;
    delete menuProfile;
    delete ui;
    delete m_login;
    delete sellDialog;
    delete sellBookDialog;
    delete database;
    delete phones;
    delete books;
    delete sortWindow;
}

void Shop::loginSuccessful(const std::string &username, std::map<std::string, User>& usersDatabase_) {
    m_login->close();
    currentUser = username;
    this->usersDatabase = usersDatabase_;
    std::string statusBarHelloMessage = currentUser + " welcome to the shop!";
    ui->statusbar->showMessage(statusBarHelloMessage.c_str());
    show();
}

void Shop::sellButtonClicked() {
    std::vector<long> uniqueIDs;

    if (ui->tabWidget->currentWidget() == phones) {
        if (sellDialog->isVisible())
            return;
        uniqueIDs = database->getUniqueID(PHONES);
        sellDialog->setID(uniqueIDs);
        sellDialog->show();
    }
    else {
        if (sellBookDialog->isVisible())
            return;
        uniqueIDs = database->getUniqueID(BOOKS);
        sellBookDialog->setID(uniqueIDs);
        sellBookDialog->show();
    }
}

void Shop::addNewItem(std::map<std::string, std::string>& data) {
    if (data.empty())
        return;
    ItemType item_type;
    QTableWidget *tableWidget;

    if (ui->tabWidget->currentWidget() == phones) {
        item_type = PHONES;
        tableWidget = phones;
    } else {
        item_type = BOOKS;
        tableWidget = books;
    }

    Item *new_item = ShopDatabase::selectCorrectChild(item_type);
    new_item->setAll(data);
    database->addRecord(item_type, new_item);
    tableWidget->setRowCount(tableWidget->rowCount() + 1);

    int row_count = tableWidget->rowCount() - 1, counter = 0;
    for (const auto &column_name: database->getHeaders(item_type))
        tableWidget->setItem(row_count, counter++, new QTableWidgetItem(data[column_name].c_str()));
    tableWidget->repaint();
}

void Shop::initializeUi() {
    ui->setupUi(this);
    ui->statusbar->setStyleSheet("QStatusBar { color: white; font: 13px;}");
    ui->sortByButton->setStatusTip("Create new window with sorting properties");
    ui->sellButton->setStatusTip("Create new item to be sold");
    ui->buyButton->setStatusTip("Buy selected item from table");
    ui->searchLineEdit->setStatusTip("Search for item in table");
    ui->searchLineEdit->setPlaceholderText("Search...");
    menuProfile = new QAction("Profile");
    menuProfile->setVisible(true);
    dbInfo = new QAction("Database info");
    dbInfo->setVisible(true);
    dbInfo->setStatusTip("Prints database items to console");
    ui->menubar->addAction(menuProfile);
    resetMenubar = new QAction("Reset");
    QFont font = resetMenubar->font();
    font.setPointSize(15);
    font.setBold(true);
    resetMenubar->setFont(font);
    resetMenubar->setVisible(false);
    ui->menubar->setStyleSheet("color: white;background-color: rgb(54, 69, 79); border-radius: 5px;");
    ui->menubar->addAction(resetMenubar);
    ui->menubar->addAction(dbInfo);
}

void Shop::initializeTab() {
    books->setEditTriggers(QAbstractItemView::NoEditTriggers);
    phones->setEditTriggers(QAbstractItemView::NoEditTriggers);
    initializeTable(PHONES, phones);
    ui->tabWidget->addTab(phones, "Phones");
    initializeTable(BOOKS, books);
    ui->tabWidget->addTab(books, "Books");
}

void Shop::initializeTable(const ItemType &item_type, QTableWidget* tableWidget) {
    std::map<ItemType, std::vector<Item *>> items;
    std::vector<std::string> headers;
    try {
        items = database->getItems();
        headers = database->getHeaders(item_type);
    } catch (std::exception &e) {
        Login::createMessageBox("Error", e.what(), QMessageBox::Critical,
                                QMessageBox::Ok | QMessageBox::NoButton);
        exit(1);
    }
    tableWidget->setStyleSheet(
            "QTableWidget { background-color: #171717; color: #FFFDE4; font: 12px; }  QHeaderView::section { border-radius: 10px; background-color: #171717; color: #FFFDE4; font: 12px; }");
    tableWidget->horizontalHeader()->setStyleSheet(
            "QHeaderView { background-color: #171717; color: #FFFDE4; font: 12px; }");
    tableWidget->verticalHeader()->setStyleSheet(
            "QHeaderView { background-color: #171717; color: #FFFDE4; font: 12px; }");
    tableWidget->verticalHeader()->setVisible(false);
    QStringList list = QStringList();

    std::for_each(headers.begin(), headers.end(),
                  [&list](const auto &header) { list << header.c_str(); });

    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels(list);
    tableWidget->setRowCount(items[item_type].size());
    int counter = 0;
    for (auto item: items[item_type]) {
        std::map<std::string, std::string> itemData = item->getAll();
        int i = 0;
        for (const auto &header: headers) {
            if (header == "Price")
                tableWidget->setItem(counter, i++, new QTableWidgetItem(QString::number(item->getPrice(), 'f', 2)));
            else
                tableWidget->setItem(counter, i++, new QTableWidgetItem(itemData[header].c_str()));
        }
        counter++;
    }
    tableWidget->resizeColumnsToContents();
}

void Shop::closeEvent(QCloseEvent *event) {
    if (m_login->isVisible() || sellDialog->isVisible() || sellBookDialog->isVisible() || userDialog->isVisible() ||
        sortWindow->isVisible()) {
        Login::createMessageBox("Warning", "Please close all windows before exit!", QMessageBox::Warning,
                                QMessageBox::Ok);
        event->ignore();
        return;
    }
    int result = QMessageBox::warning(this, "Confirm exit", "Are you sure you want to quit?",
                                      QMessageBox::Ok | QMessageBox::Cancel);
    if (result == QMessageBox::Ok) {
        std::ofstream file("../data/users.bin", std::ios::binary);
        for (auto &[id, user]: usersDatabase) {
            user.saveToBinary(file);
        }
        database->saveData();
        event->accept();
    } else
        event->ignore();
}

void Shop::sortData(const std::string& column, bool ascending) {
    if (resetMenubar->isVisible())
        resetClicked();
    ItemType item_type;
    if (ui->tabWidget->currentWidget() == phones) {
        sorted = phones;
        item_type = PHONES;
    } else {
        item_type = BOOKS;
        sorted = books;
    }
    try {
        sorted->clearContents();
        database->sortBy(item_type, column, ascending);
        initializeTable(item_type, sorted);
    } catch (const std::exception &e) {
        Login::createMessageBox("Error", e.what(), QMessageBox::Critical,
                                QMessageBox::Ok | QMessageBox::NoButton);
    }
}

void Shop::createSortWindow() {
    if (sortWindow->isVisible())
        return;
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
    long id = tableWidget->item(row, 0)->text().toLong();
    std::pair<ItemType, long> pair(item_type, id);
    Item *item_to_be_sold = (*database)[pair];
    double item_price = item_to_be_sold->getPrice();
    if (item_price > usersDatabase[currentUser].getMoney()) {
        Login::createMessageBox("Inforamtion", "You don't have enough credits to buy this item!\n\tAdd some credits.",
                                QMessageBox::Information, QMessageBox::Ok | QMessageBox::NoButton);
        return;
    }
    usersDatabase[currentUser].subtractCredits(item_price);
    *database -= pair;
    std::string soldItem;
    usersDatabase[currentUser];
    int counter = 0;
    for (const auto &header: database->getHeaders(item_type)) {
        soldItem += tableWidget->item(row, counter++)->text().toStdString() + "  ";
    }
    soldItem.pop_back();
    soldItem.pop_back();
    tableWidget->removeRow(row);
    tableWidget->update();
    tableWidget->setCurrentCell(-1, -1);
    usersDatabase[currentUser].appendHistory(soldItem);
    Login::createMessageBox("Information", "You have bought a new item :)", QMessageBox::Information,
                            QMessageBox::Ok | QMessageBox::NoButton);
}

void Shop::searchForData() {
    ItemType item_type;
    std::string search_data = ui->searchLineEdit->text().toStdString();
    ui->searchLineEdit->clear();

    if (ui->tabWidget->currentWidget() == phones) {
        sorted = phones;
        item_type = PHONES;
    } else {
        sorted = books;
        item_type = BOOKS;
    }
    sorted->clearContents();
    sorted->setRowCount(0);
    std::vector<std::string> headers = database->getHeaders(item_type);
    int counter = 0;
    for (auto &item: database->getItems()[item_type]) {
        if (item->contains(search_data)) {
            std::map<std::string, std::string> itemData = item->getAll();
            int i = 0;
            sorted->insertRow(counter);
            for (const auto &header: headers)
                sorted->setItem(counter, i++, new QTableWidgetItem(itemData[header].c_str()));
            ++counter;
        }
    }
    sorted->resizeColumnsToContents();
    resetMenubar->setVisible(true);
}

void Shop::resetClicked() {
//    if (ui->tabWidget->currentWidget() == phones) {
//        initializeTable(PHONES,phones);
//    } else
//        initializeTable(BOOKS, books);
    if (sorted)
        initializeTable(PHONES, sorted);
    sorted = nullptr;
    resetMenubar->setVisible(false);
}

void Shop::profileClicked() {
    if (userDialog->isVisible())
        return;
    userDialog->initializeListView(&usersDatabase[currentUser]);
    userDialog->show();
}

void Shop::connectSlots() noexcept {
    connect(m_login, &Login::loginSuccessful, this, &Shop::loginSuccessful);
    connect(ui->sellButton, SIGNAL(clicked()), this, SLOT(sellButtonClicked()));
    connect(sellDialog, &SellDialog::sendData, this, &Shop::addNewItem);
    connect(ui->sortByButton, SIGNAL(clicked()), this, SLOT(createSortWindow()));
    connect(sortWindow, &SortWindow::sortDataBy, this, &Shop::sortData);
    connect(ui->buyButton, SIGNAL(clicked()), this, SLOT(buyButtonClicked()));
    connect(ui->searchLineEdit, SIGNAL(returnPressed()), this, SLOT(searchForData()));
    connect(resetMenubar, SIGNAL(triggered()), this, SLOT(resetClicked()));
    connect(menuProfile, SIGNAL(triggered()), this, SLOT(profileClicked()));
    connect(sellBookDialog, &SellBookDialog::sendData, this, &Shop::addNewItem);
    connect(dbInfo, SIGNAL(triggered()), this, SLOT(printDBInfo()));
}

void Shop::initializePointers() noexcept {
    sellDialog = new SellDialog();
    sellBookDialog = new SellBookDialog();
    sortWindow = new SortWindow();
    userDialog = new UserDialog();
    m_login = new Login();
    phones = new QTableWidget(this);
    books = new QTableWidget(this);
}

void Shop::printDBInfo() {
    database->printDB();
}