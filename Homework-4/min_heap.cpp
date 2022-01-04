#include "min_heap.h"

bool isEmpty(MinHeap heap){
    return heap.size == 0;
}

void shiftUp(MinHeap &heap, int i){
    int n = heap.size;
    while(heap.arr[i].priority < heap.arr[(i-1)/2].priority && i!=0){
        swap(heap.arr[i], heap.arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

void shiftDown(MinHeap &heap, int index){
    int n = heap.size;
    int i = index;
    int min = i;
    if(n > i*2+1 && heap.arr[i*2 + 1].priority < heap.arr[i].priority)
        min = i*2 + 1;
    
    if(n > i*2+2 && heap.arr[i*2 + 2].priority < heap.arr[min].priority)
        min = i*2 + 2;
    
    if(min != i){
        swap(heap.arr[i], heap.arr[min]);
        shiftDown(heap, min);
    }
}

void Insert(MinHeap &heap, string id, unsigned int prior){
    if(isEmpty(heap)){
        heap.arr[0].id = id;
        heap.arr[0].priority = prior;
        heap.size++;
    } else {
        heap.arr[heap.size].id = id;
        heap.arr[heap.size].priority = prior;
        heap.size++;
        shiftUp(heap, heap.size - 1);
    }
}

Item Extract(MinHeap &heap){
    int n = heap.size;
    swap(heap.arr[0], heap.arr[n-1]);
    Item res = heap.arr[n-1];
    heap.size--;
    shiftDown(heap, 0);
    return res;
}

void Remove(MinHeap &heap, string id){
    int n = heap.size;
    for(int i = 0; i < n; i++){
        if(heap.arr[i].id == id){
            swap(heap.arr[n-1], heap.arr[i]);
            heap.size--;
            if(heap.arr[i].priority < heap.arr[(i-1)/2].priority )
                shiftUp(heap, i);
            else shiftDown(heap, i);
            break;
        }
    }
}

void changePriority(MinHeap &heap, string id, unsigned int prior){
    int n = heap.size;
    for(int i = 0; i < n; i++){
        if(heap.arr[i].id == id){
            heap.arr[i].priority = prior;
            if(heap.arr[i].priority < heap.arr[(i-1)/2].priority )
                shiftUp(heap, i);
            else shiftDown(heap, i);
            break;
        }
    }

}

void showHeap(MinHeap heap){
    int n = heap.size;
    for(int i = 0; i < n; i++)
        cout << "Id: " << heap.arr[i].id << ", priority: " << heap.arr[i].priority << endl;
}