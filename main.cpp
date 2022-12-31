// #include "exception.h"
// #include "book.h"
#include "database.h"
#include "phone.h"

using namespace std;

template <typename K, typename V>
void printMap(const map<K, V> &m) {
    for (const auto &[key, value] : m) {
        cout << key << ": " << value << endl;
    }
}

int main(int argc, char* argv[]) {
    Item* a = new Book;
    // a->setAll();
    // cout << a->saveToDatabase().str() << endl;
    string d = "J.K. Rowling,\"The first Harry Potter book\",1,Harry Potter and the Philosopher's Stone,10.99,Fiction";
    stringstream str(d);
    // // a->readFromStr(str);
    // // printMap<string, string>(a->getAll());
    map<string, ItemType> m ={{(string)"../data/books_database.csv", BOOKS},{(string)"../data/phones_database.csv", PHONES}};
    ShopDatabase* db=new ShopDatabase(m);

    // Item* ph = new Phone;
    // ph->setAll();
    // printMap<string, string>(ph->getAll());
    // cout << ph->saveToDatabase() << endl;
    db->printDB();
    db->addRecord(PHONES);
    db->deleteRecord(BOOKS, 1);
    db->printDB();
    db->saveData();
    // pair<ItemType, int> p(BOOKS, 22);
    // *db -= p;
    // // *db -=
    // db->saveData();

}