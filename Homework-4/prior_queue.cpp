#include "prior_queue.h"


Node* creatNode(string id, unsigned int prior){
    Node* res = new Node;
    res->id = id;
    res->priority = prior;
    return res;
}

bool isEmpty(List list){
    return list.head == nullptr;
}

void updateOrder(List &list){
    int i = 0;
    for(Node* tmp = list.head; tmp; tmp = tmp->next ){
        tmp->order = i;
        i++;
    }
}

void Insert(List &list, string id, unsigned int prior){
    Node *node = creatNode(id, prior);
    Node* tmp = list.head;
    int order = 0;
    if(isEmpty(list)){
        list.head = node;
        node->next = nullptr;
        node->order = 0;
        return;
    }
    if (node->priority < list.head->priority) {
        node->next = list.head;
        list.head = node;
        updateOrder(list);
        return;
    }
    for(; tmp->next; tmp = tmp->next ){
        if(tmp->next->priority > prior){
            node->next = tmp->next;
            tmp->next = node;
            updateOrder(list);
            return;
        }
    }
    tmp->next = node;
}

Node* Extract(List &list){
    if(isEmpty(list)) return nullptr;
    Node *res = new Node;
    res = list.head;
    list.head = list.head->next;
    res->next = nullptr;
    updateOrder(list);
    return res;
}

void Remove(List &list, string id){
    for(Node* tmp = list.head; tmp->next; tmp = tmp->next ){
        if (tmp->next->id == id){
            Node* tmp2 = tmp->next;
            tmp->next = tmp2->next;
            delete tmp2;
            updateOrder(list);
            return;
        }
    }   
}

void changePriority(List &list, string id, int prior){
    Node* prev = list.head;
    for(Node* tmp = list.head; tmp; tmp = tmp->next ){
        if (tmp->id == id){
            tmp->priority = prior;
            if (tmp->priority > prev->priority && tmp->priority < tmp->next->priority) return;
            prev->next = tmp->next;
            Insert(list, tmp->id, tmp->priority);
            delete tmp;
            tmp = nullptr;
            updateOrder(list);
            return;
        }
        prev = tmp;
    }  
}

void deleteHead(List &list){
    if(isEmpty(list)) return;
    Node* tmp = list.head;
    list.head = list.head->next;
    delete tmp;
    tmp = nullptr;
    updateOrder(list);
}

void Destructor(List &list){
    while(!isEmpty(list)){
        deleteHead(list);
    }
}

void showList(List &list){
    for(Node* tmp = list.head; tmp; tmp = tmp->next ){
        cout << "uu tien: " << tmp->priority << ", id: " << tmp->id << ", order: " << tmp->order << endl;
    }
}