//
// Created by barto on 1/11/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SellDialog.h" resolved

#include "selldialog.h"
#include "ui_SellDialog.h"


SellDialog::SellDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::SellDialog) {
    ui->setupUi(this);
//    show();
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearText()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(closeClicked()));
}

SellDialog::~SellDialog() {
    delete ui;
}

//void SellDialog::newData(std::map<std::string, std::string> &data) {
//
//}
void SellDialog::clearText() {
    ui->nameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->manufacturerLineEdit->clear();
    ui->descriptionLineEdit->clear();
    ui->specsLineEdit->clear();
    ui->idLineEdit->clear();
}

void SellDialog::okClicked() {
    std::map<std::string, std::string> data;
    if (ui->nameLineEdit->text().isEmpty() ||
        ui->priceLineEdit->text().isEmpty() ||
        ui->manufacturerLineEdit->text().isEmpty() ||
        ui->descriptionLineEdit->text().isEmpty() ||
        ui->specsLineEdit->text().isEmpty() ||
        ui->idLineEdit->text().isEmpty()) {
        Login::createMessageBox("Warning", "All fields shall be filled!", QMessageBox::Critical, QMessageBox::Ok | QMessageBox::NoButton);
        return;
    }
    data["name"] = ui->nameLineEdit->text().toStdString();
    data["price"] = ui->priceLineEdit->text().toStdString();
    data["manufacturer"] = ui->manufacturerLineEdit->text().toStdString();
    data["description"] = ui->descriptionLineEdit->text().toStdString();
    data["specs"] = ui->specsLineEdit->text().toStdString();
    data["id"] = ui->idLineEdit->text().toStdString();
    emit sendData(data);
    clearText();
    close();
}

void SellDialog::closeClicked() {
    clearText();
    close();
}
