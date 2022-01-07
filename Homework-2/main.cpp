#include "TableManager.h"

TableManager tableManager;

string charPointerToString(char *s) {
    string res(s);
    return res;
}

int toInt(string s) {
    int res = 0;
    for (int i = 0; i < s.size(); i++) {
        res = res * 10 + s[i] - '0';
    }
    return res;
}

void readDB() {
    ifstream fin("database.txt");
    tableManager.read(fin);
    fin.close();
}

void printDB() {
    ofstream fout("database.txt");
    tableManager.print(fout);
    fout.close();
}

int main(int argc, char **argv) {
    readDB();
    string *argvS = new string[argc];
    for (int i = 0; i < argc; i++)
        argvS[i] = charPointerToString(argv[i]);
    int cnt = 0;
    string req = argvS[++cnt];
    string name = argvS[++cnt];
    if (req == "make") {
        string type = argvS[++cnt];
        ++cnt;
        int len = argc - cnt;
        int *data = new int[len];
        for (int i = 0; i < len; i++) {
            data[i] = toInt(argvS[i + cnt]);
        }
        tableManager.addTable(new Table(name, type, data, len));
    } else if (req == "query") {
        int left = toInt(argvS[++cnt]);
        int right = toInt(argvS[++cnt]);
        Table *table = tableManager.getTable(name);
        if (table == NULL) {
            cout << "Table " << name << " does not exist." << endl;
        } else {
            // cout << table->getType() << " of " << table->getName();
            // cout << " from " << left << " to " << right << " is: ";
            cout << table->query(left, right) << endl;
        }
    }
    printDB();
}
