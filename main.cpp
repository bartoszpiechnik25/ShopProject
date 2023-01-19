#include <QApplication>
#include <QPushButton>
#include "shop.h"

using namespace std;

void printMap(const map<string, string>& data) {
    for (const auto& [key, value] : data) {
        cout << key << " " << value << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc > 3) {
        cerr << "There should be 2 command line arguments!\nAborting!" << endl;
        exit(EXIT_FAILURE);
    }
    QApplication a(argc, argv);
//    qApp->setStyleSheet("QPushButton {	background-color: rgb(67,70,75); border-width: 2px; border-radius: 10px; border-color: beige; font: bold 12px; color: white; padding: 5px;} QPushButton:pressed { border-style: inset; border: 2px solid black;}");
//    QPushButton button("Hello world!", nullptr);
//    button.resize( 200, 100 );
//    button.show();
//    Login l = Login();
//    ShopDatabase* db=new ShopDatabase((string)"../data/phones_database.csv", PHONES);
//    db->printDB();
//    ofstream file("../data/users.bin", ios::binary);
//    User first("artur", "koks", 345.00);
//    first.saveToBinary(file);
//    first.saveToBinary(file);
//    second.saveToBinary(file);
//    file.close();
//    ifstream file("../data/users.bin", ios::binary);
//    User loaded;
//    loaded.readFromBinary(file);
//    file.close();
//    cout << loaded.getUsername() << "  " << loaded.getPassword() <<endl;
//    for(auto &it:loaded.getHistory())
//        cout << it << endl;
    Shop s = Shop();
//    Book* book = new Book;
////    book->setAll({{"title", "Harry Potter"}, {"author", "J.K. Rowling"}, {"price", "20"}, {"pages", "300"}});
//    book->setID(1);
//    book->setPrice(20.00);
//    book->setName("Harry Potter");
//
//    map<string, string> data;
//    data["ID"] = "1";
//    data["Price"] = "20.00";
//    data["Name"] = "Harry Potter";
//    data["Type"] = "Fantasy";
//    data["Author"] = "J.K. Rowling";
//    data["Description"] = "A nice book about young wizzard";
//    book->setAll(data);
//
//    ofstream file("../binary.bin", ios::binary);
//    book->saveToBinary(file);
//    file.close();
//
//
//    ifstream file2("../binary.bin", ios::binary);
//    Book* test = new Book;
//    test->readBinary(file2);
//    file2.close();
//
//    for(auto& [key, value]: test->getAll()) {
//        cout << key << " " << value << endl;
//    }
//    printMap()
//    if (Login::exec() == QDialog::Accepted
    return QApplication::exec();
}
