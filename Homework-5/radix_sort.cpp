#include "radix_sort.h"

void readRadixSort(LinkedList& lList, int &n, int &k){
    ifstream fi("input.txt");
    if(!fi.is_open()){
        cout << "cannot open file!\n";
        return;
    }
    fi >> k >> n;
    int tmp;
    Node* curr, *prev;
    curr = nullptr; 
    prev = nullptr;
    for (int i = 0; i < n; i++){
        fi >> tmp;
        curr = new Node;
        curr->key = tmp;
        curr->next = nullptr;
        if (lList.head == nullptr){
            lList.head = curr;
        }
        else{
            prev->next = curr;
        }
        prev = curr;
    }
    fi.close();
}

int getNum(int key, int k, int num){
    int pow = 1, i = 1;
    while (i < k+1){
        pow *= 10;
        i++;
    }
    while (num > 0){
        key /= pow;
        num--;
    }
    return (key % pow);
}

void addList(MultiLL &list, Node*& node, Node*& next, int k, int t){
    int num = getNum(node->key, k, t);
    Bucket* bucket1, *bucket2;
    bucket2 = list.head;
    bucket1 = list.head->next;
    
    next = node->next;
    node->next = nullptr;

    while(bucket1 != nullptr && bucket1->id < num){
        bucket2 = bucket1;
        bucket1 = bucket1->next;
    }
    if (bucket1!=nullptr && bucket1->id == num){
        bucket1->tail->next = node;
        bucket1->tail = node;
    }
    else {
        Bucket* bucket = new Bucket;
        bucket->head = node;
        bucket->tail = node;
        bucket->id = num;
        bucket2->next = bucket;
        bucket->next = bucket1;
    }
}

void createList(MultiLL& mList, LinkedList& lList, int k, int t){
    mList.head = new Bucket;
    mList.tail = mList.head;
    mList.head->id = -1;
    mList.head->head = nullptr;
    mList.head->tail = nullptr;
    mList.head->next = nullptr;

    Node* next = nullptr, *node = lList.head;

    while (node != nullptr){
        addList(mList, node, next, k, t);
        node = next;
    }
}

void getList(MultiLL& mList, LinkedList& lList){
    Bucket* bucket1, *bucket2;
    bucket2 = mList.head;
    bucket1 = mList.head->next;

    lList.head = bucket1->head;
    bucket1 = bucket1->next; bucket2 = bucket2->next;

    for(;bucket1; bucket1 = bucket1->next){
        bucket2->tail->next = bucket1->head;
        delete bucket2;
        bucket2 = nullptr;
        bucket2 = bucket1;
    }
}

void printList(const LinkedList& lList){
    for (Node* node = lList.head; node; node = node->next){
        cout << node->key << " ";
    }
    cout << '\n';
}

void RadixSort(LinkedList& lList, MultiLL& mList, int k){
    int i = 0;
    while (i < 10/k + 1){
        createList(mList, lList, k, i);
        getList(mList, lList);
        i++;
    }
}

void delList(LinkedList& lList){
    Node* next, *curr;
    next = nullptr;
    curr = lList.head;
    
    for (;curr != nullptr; curr = next){
        next = curr->next;
        delete curr;
    }
}
