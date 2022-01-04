#include "prior_queue.h"
#include "min_heap.h"

// Priority Queue using linked list
void demoUsingLList(){
    cout << "Priority Queue su dung Linked List\n";
    List list;
    Insert(list, "12GD-FR", 4);
    Insert(list, "32EN-CN", 1);
    Insert(list, "03US-VN", 2);
    Insert(list, "96PL-RS", 8);
    Insert(list, "22MX-AR", 6);
    cout << "Cac phan tu trong list la:\n";
    showList(list);

    Node * res = Extract(list);
    cout << "\nPhan tu do uu tien cao nhat la: " << res->id << endl;
    cout << "Q sau khi bo phan tu co do uu tien cao nhat va 22MX-AR:\n";
    Remove(list, "22MX-AR");
    showList(list);
    
    changePriority(list, "96PL-RS -> 1", 1);
    cout << "\nThay doi priority cua phan tu 96PL-RS: \n";
    showList(list);
    delete res;
    res = nullptr;
    Destructor(list);
}

// priority queue using min-heap
void demoUsingHeap(){
    MinHeap heap;
    cout << "==========================================\nPriority Queue su dung Min heap\n";
    Insert(heap, "CMT-8", 3);
    Insert(heap, "30-04", 7);
    Insert(heap, "DDR4", 1);
    Insert(heap, "CA-MX", 2);
    Insert(heap, "RTX-3050", 4);
    showHeap(heap);
    Item max = Extract(heap);
    cout << "\nLay phan tu lon nhat: " << max.id << ", priority: " << max.priority << endl;
    Remove(heap, "CMT-8");
    cout << "Xoa id: CMT-8\n";
    showHeap(heap);

    cout << "\nDoi priority cua RTX-3050: 1\n";
    changePriority(heap, "RTX-3050", 1);
    showHeap(heap); 
}

int main(){
    demoUsingLList();
    demoUsingHeap();
}