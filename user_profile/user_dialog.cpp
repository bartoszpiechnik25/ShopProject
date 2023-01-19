//
// Created by barto on 1/18/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_user_dialog.h" resolved

#include "user_dialog.h"
#include "ui_user_dialog.h"


UserDialog::UserDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::UserDialog) {
    ui->setupUi(this);
    ui->doubleSpinBox->setMaximum(1000000);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->addMoneyButton, SIGNAL(clicked()), this, SLOT(addMoney()));
    connect(ui->changePasswordButton, SIGNAL(clicked()), this, SLOT(changePassword()));
    connect(ui->passwordLineEdit, SIGNAL(returnPressed()), this, SLOT(changePassword()));
}

UserDialog::~UserDialog() {
    delete ui;
}

void UserDialog::initializeListView(User* user_) {
    this->user = user_;
    ui->usernameFromCode->setText(user->getUsername().c_str());
    ui->moneyFromCode->setText(std::to_string(user->getMoney()).c_str());
    for(auto& element: user->getHistory()) {
        ui->listWidget->insertItem(0, QString(element.c_str()));
    }
}

void UserDialog::closeEvent(QCloseEvent *event) {
    ui->listWidget->clear();
    ui->moneyFromCode->clear();
    ui->usernameFromCode->clear();
}

void UserDialog::addMoney() {
    double value = ui->doubleSpinBox->text().toDouble();
    user->addCredits(value);
    ui->doubleSpinBox->clear();
    ui->moneyFromCode->setText(std::to_string(user->getMoney()).c_str());
}

void UserDialog::changePassword() {
    std::string new_password = ui->passwordLineEdit->text().toStdString();
    if (new_password.empty()) {
        Login::createMessageBox("Warning", "Password cannot be empty", QMessageBox::Warning,
                                QMessageBox::Ok | QMessageBox::NoButton);
        ui->passwordLineEdit->clear();
        return;
    }
    if (std::find(new_password.begin(), new_password.end(), ' ') != new_password.end()) {
        Login::createMessageBox("Warning", "Password cannot contain space!", QMessageBox::Warning,
                                QMessageBox::Ok | QMessageBox::NoButton);
        ui->passwordLineEdit->clear();
        return;
    }
    if (new_password == user->getPassword()) {
        Login::createMessageBox("Warning", "Password is the same!", QMessageBox::Warning,
                                QMessageBox::Ok | QMessageBox::NoButton);
        ui->passwordLineEdit->clear();
        return;
    }
    user->setPassword(new_password);
    Login::createMessageBox("Information", "Password changed successfully!", QMessageBox::Information,
                            QMessageBox::Ok | QMessageBox::NoButton);
    ui->passwordLineEdit->clear();
    ui->doubleSpinBox->clear();
}
