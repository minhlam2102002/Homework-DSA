#include <iostream>
#include <string>

using namespace std;

struct Node{
    string id;
    unsigned int order = 0;
    unsigned int priority;
    Node* next = nullptr;
};

struct List{
    Node* head = nullptr;
};

Node* creatNode(string id, unsigned int prior);
bool isEmpty(List list);
void Insert(List &list, string id, unsigned int prior);
Node* Extract(List &list);
void Remove(List &list, string id);
void changePriority(List &list, string id, int prior);
void deleteHead(List &list);
void Destructor(List &list);
void showList(List &list);