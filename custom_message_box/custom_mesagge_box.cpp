//
// Created by barto on 1/14/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_custom_mesagge_box.h" resolved

#include "custom_mesagge_box.h"
#include "ui_custom_mesagge_box.h"


CustomMesaggeBox::CustomMesaggeBox(QWidget *parent) :
        QDialog(parent), ui(new Ui::CustomMesaggeBox) {
    ui->setupUi(this);
}

CustomMesaggeBox::~CustomMesaggeBox() {
    delete ui;
}
