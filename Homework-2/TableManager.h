#ifndef TABLEMANAGER_H_INCLUDED
#define TABLEMANAGER_H_INCLUDED
#include "Table.h"
class TableManager {
   private:
    Table *_tables;
    int _len;
    const int _max_len = 5;

   public:
    TableManager();
    ~TableManager();

    bool addTable(Table *t);
    Table *getTable(string name);
    void read(ifstream &fin);
    void print(ofstream &fout);
};

#endif  // TABLEMANAGER_H_INCLUDED
