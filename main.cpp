#include <QApplication>
#include "shop.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc > 3) {
        cerr << "There should be 2 or 0 command line arguments!\nAborting!" << endl;
        exit(EXIT_FAILURE);
    }
    QApplication a(argc, argv);
    Shop s = Shop();
    return QApplication::exec();
}
