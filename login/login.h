//
// Created by barto on 1/9/2023.
//

#ifndef SHOPPROJECTQT_LOGIN_H
#define SHOPPROJECTQT_LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <map>
#include <string>
#include <thread>
#include <fstream>
#include <iostream>
#include <QCloseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QDialog {
Q_OBJECT
private:
    Ui::Login *ui;
    std::map<std::string, std::string> usersDatabase;
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login() override;
    [[nodiscard]]std::string getUsername() const;
    [[nodiscard]]std::string getPasswd() const;
    static void createMessageBox(const char* title, const char* text, QMessageBox::Icon icon, QMessageBox::StandardButtons buttons);
public slots:
    void enteredPasswd();
    void addUser();
    void cancelClicked();
signals:
    void loginSuccessful(const std::string& username);
private:
    void loadUsersDatabase();
    void writeUsersDatabase();
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};


#endif //SHOPPROJECTQT_LOGIN_H
