//
// Created by barto on 1/11/2023.
//

#ifndef SHOPPROJECTQT_SELLDIALOG_H
#define SHOPPROJECTQT_SELLDIALOG_H

#include <QDialog>
#include <algorithm>
#include "login.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SellDialog; }
QT_END_NAMESPACE

class SellDialog : public QDialog {
Q_OBJECT

public:
    explicit SellDialog(QWidget *parent = nullptr);

    ~SellDialog() override;
    void setID(std::vector<long>& id_) noexcept;
signals:
    void sendData(std::map<std::string, std::string>& data);
public slots:
    void clearText();
    void okClicked();
    void closeClicked();

private:
    Ui::SellDialog *ui;
    std::vector<long> uniqueIDs;
};


#endif //SHOPPROJECTQT_SELLDIALOG_H
