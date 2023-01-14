#include "selldialog.h"
#include "ui_selldialog.h"

SellDialog::SellDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::SellDialog) {
    ui->setupUi(this);
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearText()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(closeClicked()));
}

SellDialog::~SellDialog() {
    delete ui;
}

void SellDialog::clearText() {
    for(auto& lineEdit: findChildren<QLineEdit*>())
        lineEdit->clear();
}

void SellDialog::okClicked() {
    std::map<std::string, std::string> data;
    for(auto& lineEdit: findChildren<QLineEdit*>()) {
        if (lineEdit->text().isEmpty()) {
            Login::createMessageBox("Warning", "All fields shall be filled!", QMessageBox::Critical, QMessageBox::Ok | QMessageBox::NoButton);
            return;
        }
    }
    for(auto& lineEdit : findChildren<QLineEdit*>()) {
        std::string lineText = lineEdit->text().toStdString();
        if (std::find(lineText.begin(), lineText.end(), ',') != lineText.end()){
            Login::createMessageBox("Warning", "Comma is not allowed in any field!", QMessageBox::Critical, QMessageBox::Ok | QMessageBox::NoButton);
            lineEdit->clear();
            return;
        }
    }
    try {
        std::stol(ui->priceLineEdit->text().toStdString());
    } catch (std::invalid_argument& e) {
        Login::createMessageBox("Warining", "Price shall be a number!", QMessageBox::Critical, QMessageBox::Ok | QMessageBox::NoButton);
        ui->priceLineEdit->clear();
        return;
    }

    try {
        std::stod(ui->priceLineEdit->text().toStdString());
    } catch (const std::invalid_argument& e){
        Login::createMessageBox("Warining", "Price shall be a number!", QMessageBox::Critical, QMessageBox::Ok | QMessageBox::NoButton);
        ui->priceLineEdit->clear();
        return;
    }
    data["Name"] = ui->nameLineEdit->text().toStdString();
    data["Price"] = ui->priceLineEdit->text().toStdString();
    data["Manufacturer"] = ui->manufacturerLineEdit->text().toStdString();
    data["Description"] = ui->descriptionLineEdit->text().toStdString();
    data["Specs"] = ui->specsLineEdit->text().toStdString();
    data["ID"] = ui->idLineEdit->text().toStdString();
    emit sendData(data);
    clearText();
    close();
}

void SellDialog::closeClicked() {
    clearText();
    close();
}