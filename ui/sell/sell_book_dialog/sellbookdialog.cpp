//
// Created by barto on 1/14/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SellBookDialog.h" resolved

#include "sellbookdialog.h"
#include "ui_SellBookDialog.h"


SellBookDialog::SellBookDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::SellBookDialog) {
    ui->setupUi(this);
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearText()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(closeClicked()));
    for(auto& lineEdit: findChildren<QLineEdit*>())
        connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(okClicked()));
}

SellBookDialog::~SellBookDialog() {
    delete ui;
}

void SellBookDialog::clearText() {
    for(auto& lineEdit: findChildren<QLineEdit*>())
        lineEdit->clear();
}

void SellBookDialog::okClicked() {
    std::map<std::string, std::string> data;
    for (auto &lineEdit: findChildren<QLineEdit *>()) {
        if (lineEdit->text().isEmpty()) {
            Login::createMessageBox("Warning", "All fields shall be filled!", QMessageBox::Critical,
                                    QMessageBox::Ok | QMessageBox::NoButton);
            return;
        }
    }
    for (auto &lineEdit: findChildren<QLineEdit *>()) {
        std::string lineText = lineEdit->text().toStdString();
        if (std::find(lineText.begin(), lineText.end(), ',') != lineText.end()) {
            Login::createMessageBox("Warning", "Comma is not allowed in any field!", QMessageBox::Critical,
                                    QMessageBox::Ok | QMessageBox::NoButton);
            lineEdit->clear();
            return;
        }
    }
    try {
        if (!SellDialog::isValidNumber(ui->idLineEdit->text().toStdString())) {
            Login::createMessageBox("Warning", "ID shall be a number!", QMessageBox::Critical,
                                    QMessageBox::Ok | QMessageBox::NoButton);
            ui->idLineEdit->clear();
            return;
        }
        long id = std::stol(ui->priceLineEdit->text().toStdString());
        if (std::find(uniqueIDs.begin(), uniqueIDs.end(), id) != uniqueIDs.end()) {
            Login::createMessageBox("Warning", "ID already exists!", QMessageBox::Critical,
                                    QMessageBox::Ok | QMessageBox::NoButton);
            ui->idLineEdit->clear();
            return;
        }
    } catch (std::invalid_argument &e) {
        Login::createMessageBox("Warining", "Price shall be a number!", QMessageBox::Critical,
                                QMessageBox::Ok | QMessageBox::NoButton);
        ui->priceLineEdit->clear();
        return;
    }
    if (!SellDialog::isValidNumber(ui->priceLineEdit->text().toStdString())) {
        Login::createMessageBox("Warning", "Price shall be a number!", QMessageBox::Critical,
                                QMessageBox::Ok | QMessageBox::NoButton);
        ui->priceLineEdit->clear();
        return;
    }

    data["Name"] = ui->nameLineEdit->text().toStdString();
    data["Price"] = ui->priceLineEdit->text().toStdString();
    data["Author"] = ui->authorLineEdit->text().toStdString();
    data["Description"] = ui->descriptionLineEdit->text().toStdString();
    data["Type"] = ui->typeLineEdit->text().toStdString();
    data["ID"] = ui->idLineEdit->text().toStdString();
    emit sendData(data);
    clearText();
    close();
}

void SellBookDialog::closeClicked() {
    clearText();
    close();
}

void SellBookDialog::setID(std::vector<long> &id_) noexcept{
    uniqueIDs = id_;
}
