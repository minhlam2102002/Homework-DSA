#include<iostream>
#include"CLList.h"

using namespace std;

int main(){
    CLinkedList list;
    for(int i = 10; i >=0 ; i--)
        list.addHead(i);
    list.printList();
    for(int i = 11; i <=20; i++)
        list.addTail(i);
    list.printList();
    list.removeHead();
    list.removeTail();
    list.printList();
    list.addAfter(999,10);
    list.printList();
    list.removeAfter(10);
    list.printList();
}