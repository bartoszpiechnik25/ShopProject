//
// Created by barto on 1/14/2023.
//

#ifndef SHOPPROJECTQT_CUSTOM_MESAGGE_BOX_H
#define SHOPPROJECTQT_CUSTOM_MESAGGE_BOX_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class CustomMesaggeBox; }
QT_END_NAMESPACE

class CustomMesaggeBox : public QDialog {
Q_OBJECT

public:
    explicit CustomMesaggeBox(QWidget *parent = nullptr);

    ~CustomMesaggeBox() override;

private:
    Ui::CustomMesaggeBox *ui;
};


#endif //SHOPPROJECTQT_CUSTOM_MESAGGE_BOX_H
