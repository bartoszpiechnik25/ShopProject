//
// Created by barto on 1/14/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SortWindow.h" resolved

#include "sortwindow.h"
#include "ui_SortWindow.h"

/**
 * @brief Create window for sorting
 * @param parent - parent widget
 */
SortWindow::SortWindow(QWidget *parent) :
        QDialog(parent), ui(new Ui::SortWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Sort Data");
    ui->ascendingCheck->setStyle(QStyleFactory::create("Fusion"));
    ui->descendingCheck->setStyle(QStyleFactory::create("Fusion"));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
}

SortWindow::~SortWindow() {
    delete ui;
}

/**
 * @brief Set data for combobox
 * @data - vector of items to be added to combobox
 */
void SortWindow::setComboBoxData(const std::vector<std::string> &data) {
    for (const auto &item : data)
        ui->comboBox->addItem(item.c_str());
}

/**
 * @brief Slot handling ok button click
 */
void SortWindow::okClicked() {
    std::string column;
    bool ascending;
    if (ui->ascendingCheck->isChecked() && ui->descendingCheck->isChecked()) {
        Login::createMessageBox("Error", "You can't choose both ascending and descending", QMessageBox::Critical,
                                QMessageBox::Ok | QMessageBox::NoButton);
        return;
    } else if (ui->ascendingCheck->isChecked()) {
        ascending = true;
    } else if (ui->descendingCheck->isChecked()) {
        ascending = false;
    } else {
        Login::createMessageBox("Error", "You have to choose ascending or descending", QMessageBox::Critical,
                                QMessageBox::Ok | QMessageBox::NoButton);
        return;
    }
    column = ui->comboBox->currentText().toStdString();
    emit sortDataBy(column, ascending);
    ui->comboBox->clear();
    ui->descendingCheck->setChecked(false);
    ui->ascendingCheck->setChecked(false);
    close();
}

/**
 * @brief Slot handling cancel button click
 */
void SortWindow::cancelClicked() {
    ui->comboBox->clear();
    ui->descendingCheck->setChecked(false);
    ui->ascendingCheck->setChecked(false);
    close();
}