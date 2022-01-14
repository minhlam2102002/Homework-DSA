#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;
struct Trailer;
struct Leader{
    int key;
    int count;
    Leader* next;
    Trailer* trail;
};

struct Trailer{
    Leader* id;
    Trailer* next;
};

Leader* addLeader(Leader* &head, Leader* &tail, int key, int& cnt);
void addTopo(Leader* a, Leader* b);
vector<pair<int, int>> readFile();
void showTopo(Leader* head, Leader* tail, int &count);
void delTopo(Leader* head, Leader* tail);
int checkType();