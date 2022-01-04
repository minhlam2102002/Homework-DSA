#include <string>
#include <iostream>
using namespace std;

struct Item{
    string id;
    unsigned int priority;
};

struct MinHeap{
    Item arr[100];
    int size = 0;
};

void Insert(MinHeap &heap, string id, unsigned int prior);
Item Extract(MinHeap &heap);
void Remove(MinHeap &heap, string id);
void changePriority(MinHeap &heap, string id, unsigned int prior);
void showHeap(MinHeap heap);