#include<iostream>

using namespace std;

int interpolaSearch(int *arr, int n, int x){
    int l=0, r=n-1;
    while(l <= r && x >= arr[l] && x <= arr[r]){
        if(l == r){
            if (arr[l] == x)
                return l;
            return -1;
        }
        int pos = l + (double)(r-l)*(x-arr[l])/(arr[r]-arr[l]);
        if(arr[pos] == x) return pos;
        if(arr[pos] < x) l = pos + 1;
        if(arr[pos] > x) r = pos - 1;
    }
    return -1;
}

int main(int argc, char *argv[]){
    if (argc == 1)
        return 0;
    int x = atoi(argv[1]);
    int *arr;
    arr = new int[argc-2];
    for(int i = 2; i < argc; i++){
        arr[i-2] = atoi(argv[i]);
    }
    cout << interpolaSearch(arr,argc-2, x) << endl;
    delete[]arr;
}