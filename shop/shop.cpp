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
    phones = new QTableWidget(this);
    sellDialog = new SellDialog();
    sellBookDialog = new SellBookDialog();
    initializeTab();
    connect(m_login, &Login::loginSuccessful, this, &Shop::loginSuccessful);
    connect(phones, &QTableWidget::cellClicked, this, &Shop::cellActivated);
    connect(ui->sellButton, SIGNAL(clicked()), this, SLOT(sellButtonClicked()));
    connect(sellDialog, &SellDialog::sendData, this, &Shop::addNewItem);
//    connect(ui->sortByButton, SIGNAL(clicked()), this, SLOT(sortData()));
}

Shop::~Shop() {
    database->saveData();
    delete ui;
    delete m_login;
    delete sellDialog;
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
    if (ui->tabWidget->currentWidget() == phones)
        sellDialog->show();
    else
        sellBookDialog->show();
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
    ui->sortingBox->setStyle(QStyleFactory::create("Fusion"));
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
    if (result == QMessageBox::Ok)
        event->accept();
    else
        event->ignore();
}
