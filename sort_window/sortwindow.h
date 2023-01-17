//
// Created by barto on 1/14/2023.
//

#ifndef SHOPPROJECTQT_SORTWINDOW_H
#define SHOPPROJECTQT_SORTWINDOW_H

#include <QDialog>
#include <QStyleFactory>
#include <QCommonStyle>
#include "login.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SortWindow; }
QT_END_NAMESPACE

class SortWindow : public QDialog {
Q_OBJECT

public:
    explicit SortWindow(QWidget *parent = nullptr);

    ~SortWindow() override;
    void setComboBoxData(const std::vector<std::string>& data);
public slots:
    void okClicked();
    void cancelClicked();
signals:
    void sortDataBy(const std::string&, bool);
private:
    Ui::SortWindow *ui;
};


#endif //SHOPPROJECTQT_SORTWINDOW_H
