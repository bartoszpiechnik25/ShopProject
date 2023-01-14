#include <QApplication>
#include <QPushButton>
#include "login/login.h"
#include "shop/shop.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    qApp->setStyleSheet("QPushButton {	background-color: rgb(67,70,75); border-width: 2px; border-radius: 10px; border-color: beige; font: bold 12px; color: white; padding: 5px;} QPushButton:pressed { border-style: inset; border: 2px solid black;}");
//    QPushButton button("Hello world!", nullptr);
//    button.resize( 200, 100 );
//    button.show();
//    Login l = Login();
//    ShopDatabase* db=new ShopDatabase((string)"../data/phones_database.csv", PHONES);
//    db->printDB();
    Shop s = Shop();

//    if (Login::exec() == QDialog::Accepted)

    return QApplication::exec();
}
