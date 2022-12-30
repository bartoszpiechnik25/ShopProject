#include "database.h"

ShopDatabase::ShopDatabase(): files(nullptr) {}

ShopDatabase::ShopDatabase(const std::vector<std::string>& paths_) {
    files = new std::ifstream [paths_.size()];
    open(paths_);
}

ShopDatabase::ShopDatabase(const std::string& path_) {
    files = new std::ifstream;
    open(path_);
}

ShopDatabase::~ShopDatabase() {
    if ( (sizeof(files) / sizeof(std::ifstream)) > 1)
        delete [] files;
    else
        delete files;
    for(const auto& [key, value]: data) {
        for(Item* it: value)
            delete it;
    }
}

void ShopDatabase::open(const std::string& path) {
    using namespace std;
    files->open(path);
    
    if (files->fail()) {
        char* s;
        sprintf(s, "Cannot open file: %s!", path.c_str());
        throw runtime_error(s);
    }
    data["Book"] = vector<Item*>();

    string header;
    ifstream non_pointer(path, files->rdbuf());

    getline(non_pointer, header);
    string line;
     
    while (getline(*files, line)) {
        stringstream stream(line);
        Item* item = new Book;
        item->readFromStr(stream);
        data["Book"].push_back(item);
    }
    files->close();
    
}

void ShopDatabase::open(const std::vector<std::string>& path) {

}

template <typename K, typename V>
void printMap(const std::map<K, V> &m) {
    for (const auto &[key, value] : m) {
        std::cout << key << ": " << value << std::endl;
    }
    std::cout << std::endl;

}

void ShopDatabase::printDB() const {
    for(const auto& [key, value]: data)
        for(Item* it: value)
            printMap<std::string, std::string>(it->getAll());
}