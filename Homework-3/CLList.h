#include<iostream>
#include"Node.h"

class CLinkedList{
public:
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    ~CLinkedList();
public:
    bool isEmpty();

    bool addHead(int data);
    bool addTail(int data);
    bool removeHead();
    bool removeTail();
    bool addAfter(int data, int val);
    bool removeAfter(int val);

    void printList();
};