#include "topo.h"
#define FILE_NAME "input.txt"

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
 
int checkType(){
    ifstream fi(FILE_NAME);
    if(!fi.is_open()){
        cout << "cannot open file\n";
        return 0;
    }
    int type;
    string s;
    char check = '(';
    fi >> s;
    if(s[0] == check)
        type = 1;
    else type = 2;
    fi.close();
    return type;
}