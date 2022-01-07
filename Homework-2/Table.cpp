#include "Table.h"

Table::Table() {
    _data = nullptr;
    _len = 0;
}

int gcd(int a, int b) { 
    return b ? gcd(b, a%b) : a; 
}
int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}
int (*get_func(string type))(int, int) {
    if(type == "MAX") return max;
    if(type == "MIN") return min;
    if(type == "GCD") return gcd;
    return nullptr;
}
int** buildSparseTable(int* data, int len, int& len_sparse, int(*func)(int, int)) {
    // build sparse table from data
    int** sparse = new int*[len];
    len_sparse = (int)log2(len) + 1;
    for(int i = 0; i < len; i++) {
        sparse[i] = new int[len_sparse];
        for(int j = 0; j < len_sparse; j++) {
            sparse[i][j] = 0;
        }
    }
    
    for(int i = 0; i < len; i++) {
        sparse[i][0] = data[i];
    }
    for(int j = 1; j < len_sparse; j++) {
        for(int i = 0; i <= len - (1 << j); i++) {
            sparse[i][j] = func(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
        }
    }
    return sparse;
}
Table::Table(string name, string type, int* data, int len) {
    _name = name;
    _type = type;
    _data = data;
    _len = len;
    _sparse = buildSparseTable(_data, _len, _len_sparse, get_func(_type));
}

Table::~Table() {
    delete[] _data;
    _data = nullptr;
}

void Table::read(ifstream &fin) {
    fin >> _name >> _type >> _len;
    _data = new int[_len];
    _sparse = new int*[_len];
    for (int i = 0; i < _len; i++) fin >> _data[i];
    _len_sparse = (int)log2(_len) + 1;
    for(int i = 0; i < _len; i++) {
        _sparse[i] = new int[_len_sparse];
        for(int j = 0; j < _len_sparse; j++) {
            fin >> _sparse[i][j];
        }
    }
}

void Table::print(ofstream &fout) {
    fout << _name << " " << _type << " " << _len << endl;
    for (int i = 0; i < _len; i++) fout << _data[i] << " ";
    fout << endl;
    for(int i = 0; i < _len; i++) {
        for(int j = 0; j <_len_sparse; j++) {
            fout << _sparse[i][j] << " ";
        }
        fout << endl;
    }
}
void Table::print(ostream& os) {
    for(int i = 0; i < _len; i++) {
        for(int j = 0; j <_len_sparse; j++) {
            os << _sparse[i][j] << " ";
        }
        os << endl;
    }
}
string Table::getName() {
    return _name;
}
string Table::getType() {
    return _type;
}
int Table::query(int left, int right) {
    int j = (int)log2(right - left + 1);
    int(*func)(int, int) = get_func(_type);
    return func(_sparse[left][j], _sparse[right - (1 << j) + 1][j]);
}
