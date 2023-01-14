//
// Created by barto on 1/14/2023.
//

#ifndef SHOPPROJECTQT_SELLBOOKDIALOG_H
#define SHOPPROJECTQT_SELLBOOKDIALOG_H

#include <QDialog>
#include "login.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SellBookDialog; }
QT_END_NAMESPACE

class SellBookDialog : public QDialog {
Q_OBJECT

public:
    explicit SellBookDialog(QWidget *parent = nullptr);

    ~SellBookDialog() override;
signals:
    void sendData(std::map<std::string, std::string>& data);
public slots:
    void clearText();
    void okClicked();
    void closeClicked();
private:
    Ui::SellBookDialog *ui;
};


#endif //SHOPPROJECTQT_SELLBOOKDIALOG_H
