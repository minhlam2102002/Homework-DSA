#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
vector<int> encoding(string input) {
    unordered_map<string, int> table;
    int table_size = 256;
    for (int i = 0; i < table_size; i++)
        table[string(1, i)] = i;
    string cur;
    vector<int> output;
    for (int i = 0; i < input.size(); i++) {
        cur += input[i];
        if (table.find(cur) == table.end()) {
            table[cur] = table_size++;
            cur.pop_back();
            output.push_back(table[cur]);
            cur = input[i];
        }
    }
    if (cur.size())
        output.push_back(table[cur]);
    return output;
}

string decoding(vector<int> input) {
    string output;
    unordered_map<int, string> table;
    int table_size = 256;
    for (int i = 0; i < table_size; i++)
        table[i] = string(1, i);
    string pre;
    for (int i = 0; i < input.size(); i++) {
        if (table.find(input[i]) == table.end()) {
            table[input[i]] = pre + pre[0];
        }
        output += table[input[i]];
        if(pre.size())
            table[table_size++] = pre + table[input[i]][0];
        pre = table[input[i]];
    }
    return output;
}
string toBase2(int n, int bit_size) {
    string s = "";
    while (n > 0) {
        s = (n % 2 == 0 ? "0" : "1") + s;
        n /= 2;
    }
    while (s.size() < bit_size)
        s = "0" + s;
    return s;
}
int calcBitSize(vector<int> &output_code) {
    int bit_size = 0;
    for (int i = 0; i < output_code.size(); i++) {
        bit_size = max(bit_size, (int)log2(output_code[i]) + 1);
    }
    return bit_size;
}
double calcPercentCompress(int input_size, int output_size, int bit_size) {
    int input_bit = input_size * sizeof(char) * 8;
    int output_bit = output_size * bit_size;
    return (double)(input_bit - output_bit) / input_bit * 100;
}
int main(int argc, char **argv) {
    char *flag = argv[1];
    cout << fixed << setprecision(2);
    if (strcmp(flag, "-c") == 0) {
        string input(argv[2]);
        vector<int> output = encoding(input);
        for (int i = 0; i < output.size(); i++)
            cout << output[i] << " ";
        cout << endl;
        int bit_size = calcBitSize(output);
        double percent = calcPercentCompress(input.size(), output.size(), bit_size);
        for (int i = 0; i < output.size(); i++) 
            cout << toBase2(output[i], bit_size) << " ";
        cout << endl;
        cout << percent << endl;
    } else {
        vector<int> input;
        for (int i = 2; i < argc; i++) 
            input.push_back(atoi(argv[i]));
        string output = decoding(input);
        cout << output << endl;
        int bit_size = calcBitSize(input);
        double percent = calcPercentCompress(output.size(), input.size(), bit_size);
        cout << percent << endl;
    }
}
