#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#define FILE_NAME "input.txt"
using namespace std;

struct Trailer;

// dinh nghia ham
struct Leader{
    int key;
    int count;
    Leader* next;
    Trailer* trail;
};

struct Trailer{
    Leader* id;
    Trailer* next;
};

Leader* addLeader(Leader* &head, Leader* &tail, int key, int& cnt){
    Leader* tmp;
    tmp = head;
    tail->key = key;
    while(tmp->key != key) tmp = tmp->next;
    if(tmp == tail){
        cnt++;
        tail = new Leader;
        tmp->count = 0;
        tmp->trail = nullptr;
        tmp->next = tail;
    }
    return tmp;
}

void addTopo(Leader* a, Leader* b){
    Trailer* trail = new Trailer;
    trail->id = b;
    trail->next = a->trail;
    a->trail = trail;
    b->count++;
}

vector<pair<int, int>> readFile() {   
    freopen(FILE_NAME, "r", stdin);
    string s; cin >> s;
    int i = 0;
    vector<pair<int, int>> res;
    while (i < s.size()) {
        int j = i + 1;
        while (s[j] != ')') j++;
        string temp = s.substr(i + 1, j - i - 1);
        int k = 0;
        while (k < temp.size()) {
            if (temp[k] == ',') temp[k] = ' ';
            k++;
        }
        stringstream ss(temp);
        int a, b;
        ss >> a >> b;
        res.push_back(make_pair(a, b));
        i = j + 1;
    }
    return res;
}

void showTopo(Leader* head, Leader* tail, int &count){
    Leader* tmp = head;
    Leader* p;
    head = nullptr;
    while(tmp!=tail){
        p = tmp;
        tmp = tmp->next;
        if(p->count == 0){
            p->next = head;
            head = p;
        }
    }

    tmp = head;
    Trailer* trail;
    while(tmp){
        cout << tmp->key << ' ';
        count--;
        trail = tmp->trail;
        tmp = tmp->next;
        while(trail){
            p = trail->id;
            p->count--;
            if(p->count == 0){
                p->next = tmp;
                tmp = p;
            }
            trail = trail->next;
        }
    }
}

void delTopo(Leader* head, Leader* tail){
    Leader* tmp = head, *next;
    Trailer* trail, *nextTrail;
    head = nullptr;
    while(tmp){
        next = tmp->next;
        trail = tmp->trail;
        while(trail){
            nextTrail = trail->next;
            delete trail;
            trail = nextTrail;
        }
        tmp = next;
    }
    tail = nullptr;
    delete tmp;
    tmp = nullptr;
}

int maxEle(vector<int> vect){
    int max = -1;
    for(auto i : vect){
        if (i > max) max = i;
    }
    return max;
}

int numberOfDigits(int a){
    int res = 0;
    while( a > 0){
        a /= 10;
        res++;
    }
    return res;
}

void countForRadix(vector<int> &vect, int mu){
    int n = vect.size();
    vector<int> output(n);
    int count[10] = { 0 };

    for (int i = 0; i < n; i++)
        count[(vect[i] / mu) % 10]++;
 

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
 

    for (int i = n - 1; i >= 0; i--) {
        output[count[(vect[i] / mu) % 10] - 1] = vect[i];
        count[(vect[i] / mu) % 10]--;
    }
 
    for (int i = 0; i < n; i++)
        vect[i] = output[i];
}
 
void RadixSort(vector<int>& vect){
    int max = maxEle(vect);
    for (int mu = 1; max / mu > 0; mu *= 10)
        countForRadix(vect, mu);
}

int main() {
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
    vector<int> test = {1,6,3,6,7,8,3,7,8,2,1,3,9};
    RadixSort(test);
    for(auto i : test) cout << i << " ";
    cout << endl;
}