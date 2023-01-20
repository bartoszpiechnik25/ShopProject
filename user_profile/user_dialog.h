//
// Created by barto on 1/18/2023.
//

#ifndef SHOPPROJECTQT_USER_DIALOG_H
#define SHOPPROJECTQT_USER_DIALOG_H

#include <QDialog>
#include "user.h"
#include "login.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UserDialog; }
QT_END_NAMESPACE

class UserDialog : public QDialog {
Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = nullptr);

    ~UserDialog() override;

    void initializeListView(User *user_);

private:
    Ui::UserDialog *ui;
    User *user;

    void closeEvent(QCloseEvent *event) override;

public slots:

    void changePassword();

    void addMoney();
};
#endif //SHOPPROJECTQT_USER_DIALOG_H
