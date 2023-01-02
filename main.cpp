#include "database.h"

using namespace std;

// template <typename K, typename V>
// void printMap(const map<K, V> &m) {
//     for (const auto &[key, value] : m) {
//         cout << key << ": " << value << endl;
//     }
// }

int main(int argc, char* argv[]) {
    // Item* a = new Book;
    // Item* b = new Book;
    // // a->setAll();
    // // cout << a->saveToDatabase().str() << endl;
    // string d = "1,To Kill a Mockingbird,Harper Lee,A story of prejudice in the South,9.99,Fiction";
    // a->readFromStr(d);

    // string c = "11,The Divine Comedy,Dante Alighieri,A journey through Hell Purgatory and Heaven,18.990000,Fiction";
    // b->readFromStr(c);

    // vector<Item*> v;
    // v.push_back(b);
    // v.push_back(a);

    // std::sort(v.begin(), v.end(), [](Item* a, Item* b) {
    //     return static_cast<Book*>(a)->getID() > static_cast<Book*>(b)->getID();
    // });
    // //print vector
    // for (Item* i : v) {
    //     printMap<string, string>(i->getAll());
    // }
    // // a->readFromStr(str);
    // // printMap<string, string>(a->getAll());
    map<string, ItemType> m ={{(string)"../data/books_database.csv", BOOKS},{(string)"../data/phones_database.csv", PHONES}};
    ShopDatabase* db=new ShopDatabase((string)"../data/phones_database.csv", PHONES);
    // db->printDB();
    db->sortBy(PHONES, "Manufacturer");
    db->printDB();
    // unique_ptr<Item> it(a);
    // it->setAll();
    // // Item* ph = new Phone;
    // // ph->setAll();
    // // printMap<string, string>(ph->getAll());
    // // cout << ph->saveToDatabase() << endl;
    // // db->printDB();
    // // db->addRecord(PHONES);
    // pair<ItemType, int> pa(PHONES, 27);
    // // db->deleteRecord(BOOKS, 1);
    // string n_phone = "234,Samsung Galaxy S22 FE,Samsung,Latest Samsung phone,1199.99,5G 3 cameras";
    // pair<ItemType, string> par(PHONES, n_phone);
    // // *db += pa;
    // *db += par;
    // db->printDB();
    // db->saveData();
    // pair<ItemType, int> p(BOOKS, 22);
    // *db -= p;
    // // *db -=
    // db->saveData();

}