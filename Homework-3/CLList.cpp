#include"CLList.h"
using namespace std;

bool CLinkedList::isEmpty(){
    return (this->head == nullptr && this->tail == nullptr);
}

bool CLinkedList::addHead(int data){
    Node *newNode = new Node(data);
    if(this->isEmpty()){
        newNode->next = newNode;
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
        tail->next = head;
    }
    return true;
}

bool CLinkedList::addTail(int data) {
    if(isEmpty()) {
        return addHead(data);
    } else {
        Node *newNode = new Node(data);
        tail->next = newNode;
        tail = newNode;
        newNode->next = head;
        return true;
    }
}

bool CLinkedList::removeHead(){
    if(isEmpty()) return false;
    if(head->next == head){
        delete head;
        head = nullptr;
        tail = nullptr;
        return true;
    }
    Node *temp = head;
    head = head->next;
    tail->next = head;
    delete temp;
    temp = nullptr;
    return true;
}

bool CLinkedList::removeTail(){
    if(isEmpty()) return false;
    if(head->next == head){
        removeHead();
    }
    Node* tmp;
    for(tmp = head; tmp->next != tail;tmp = tmp->next);
    delete tail;
    tail = tmp;
    tail->next = head;
    tmp = nullptr;
    return true;
}

bool CLinkedList::addAfter(int data, int val){
    if(isEmpty()) 
        return false;
    Node* tmp = head;
    for(; tmp->data != val && tmp != tail; tmp = tmp->next);
    if(tmp->data !=val) return false;
    Node* tmp2 = new Node(data);
    tmp2->next = tmp->next;
    tmp->next = tmp2;
    return true;
}

bool CLinkedList::removeAfter(int val) {
    // remove the node after the node with val
    if(isEmpty()) return false;
    Node* tmp;
    for(tmp = head; tmp->data != val && tmp->next != tail; tmp = tmp->next);
    if(tmp->next == tail && tmp->data !=val) return false;
    Node* tmp2 = tmp->next;
    tmp->next = tmp2->next;
    delete tmp2;
    tmp2 = nullptr;
    return true;
}

void CLinkedList::printList() {
    if(isEmpty()) return;
    for(Node* tmp = head; tmp != tail; tmp = tmp->next) {
        cout << tmp->data << ' ';
    }
    cout << tail->data << endl;
}

CLinkedList::~CLinkedList(){
    while(!isEmpty()){
        removeHead();
    }
}