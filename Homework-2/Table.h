#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Table {
private:
    string _name, _type;
    int _len, _len_sparse;
    int* _data;
    int** _sparse;
public:
    Table();
    Table(string name, string type, int* data, int len);
    ~Table();
public:
    string getName();
    string getType();
    void read(ifstream& fin);
    void print(ofstream& fout);
    void print(ostream& os);
    int query(int left, int right);
};

#endif  // TABLE_H_INCLUDED
