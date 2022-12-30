// #include "exception.h"
// #include "book.h"
#include "database.h"

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
    ShopDatabase* db=new ShopDatabase((string)"../data/books_database.csv", BOOKS);
    // db->printDB();
    // try {
    //     db->deleteRecord(BOOKS, 23);
    // } catch (const std::out_of_range& e) {
    //     cout << e.what() << endl << "Handle exception" << endl;
    //     db->deleteRecord(BOOKS, 22);
    // }
    // db->printDB();
    // bool* mod = new bool [1];
    // delete [] mod;

    pair<ItemType, int> p(BOOKS, 22);
    *db -= p;
    // *db -=
    db->saveData();

}