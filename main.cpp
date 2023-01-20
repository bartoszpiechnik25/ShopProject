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
    cout << std::thread::hardware_concurrency() << endl;
    QApplication a(argc, argv);
    Shop s = Shop();
    return QApplication::exec();
}
