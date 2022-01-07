#include "TableManager.h"

TableManager::TableManager() {
    _tables = new Table[_max_len];
    _len = 0;
}

TableManager::~TableManager() {
    delete[] _tables;
}

void TableManager::read(ifstream &fin) {
    fin >> _len;
    for (int i = 0; i < _len; i++) {
        _tables[i].read(fin);
    }
}

void TableManager::print(ofstream &fout) {
    fout << _len << endl;
    for (int i = 0; i < _len; i++) {
        _tables[i].print(fout);
    }
}
Table *TableManager::getTable(string name) {
    for (int i = 0; i < _len; i++) {
        if (_tables[i].getName() == name) return &_tables[i];
    }
    return nullptr;
}
bool TableManager::addTable(Table *t) {
    if (_len == _max_len) {
        cout << "TableManager is full" << endl;
        delete t;
        return false;
    }
    Table *tmp = getTable(t->getName());
    if (tmp != nullptr) {
        tmp = t;
    } else {
        _tables[_len++] = *t;
    }
    t->print(cout);
    return true;
}
