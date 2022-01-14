#include "radix_sort.h"
#include "topo.h"

int main() {
    int type = checkType();
    if(type == 1){
        vector<pair<int, int>> input = readFile();
        Leader* head = new Leader;
        Leader* a, *b, *tail = head;
        int cnt = 0;
        for(auto i : input){
            a = addLeader(head, tail, i.first, cnt);
            b = addLeader(head, tail, i.second, cnt);
            addTopo(a, b);
        }
        showTopo(head, tail, cnt);
        delTopo(head, tail);
        cout << endl;
    } else if (type == 2){
        LinkedList lList;
        lList.head = nullptr;
        MultiLL mList;
        int n, k;
        readRadixSort(lList, n, k);
        RadixSort(lList, mList, k);
        printList(lList);
        delList(lList);
    }
}