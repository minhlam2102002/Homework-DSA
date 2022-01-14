#pragma once
#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    int key;
    Node* next;
};

struct Bucket {
    int id;
    Node* head, *tail;
    Bucket* next;
};


struct MultiLL {
    Bucket* head;
    Bucket* tail;
};

struct LinkedList{
    Node* head;
};

void readRadixSort(LinkedList&, int &, int &);
int getNum(int, int, int);
void addList(MultiLL &, Node* &, Node*&, int, int);
void createList(MultiLL&, LinkedList&, int, int);
void getList(MultiLL&, LinkedList&);
void printList(const LinkedList&);
void RadixSort(LinkedList&, MultiLL&, int);
void delList(LinkedList&);