#include "Trie.h"

void Insert(TrieNode* &Dic, string word, int id){
    TrieNode* pTrie = Dic;
    for(int i = 0; i <  word.length(); i++){
        int index = word[i] - 'a';
        if(pTrie->next[index] == nullptr)
                pTrie->next[index] = new TrieNode;
        pTrie = pTrie->next[index];
    }
    pTrie->ID = id;
}

void creatTrie(TrieNode* &Dic, string DicFile){
    ifstream fi(DicFile);
    if(!fi.is_open()){
        cout << "Can not open the file\n";
        return;
    }
    string tmp;
    vector<string> tmp2;
    int id = 1;
    Dic->ID = -1;
    while(getline(fi, tmp)){
        TrieNode* pTrie = Dic;
        tmp2 = Tokenizer::parse(tmp, SEP);
        tmp = tmp2[1];
        for(int i = 0; i <  tmp.length() - 1; i++){
            int index = tmp[i] - 'a';
            if(pTrie->next[index] == nullptr)
                pTrie->next[index] = new TrieNode;
            pTrie = pTrie->next[index];
        }
        pTrie->ID = id;
        id++;
    }
    fi.close();
}

int lookup(TrieNode* &Dic, string word){
    TrieNode* pTrie = Dic;
    for(int i = 0; i <  word.length(); i++){
        pTrie = pTrie->next[word[i] - 'a'];
    }
    return pTrie->ID;    
}

void findAll(TrieNode* &root, vector<string> &result, string prefix){
    if(root->ID != 0)
        result.push_back(prefix);
    for(int i = 0; i < SIZE; i++){
        if(root->next[i] != nullptr){
            findAll(root->next[i], result, prefix + (char)(i + 'a'));
        }
    }
}

vector<string> lookupPrefix(TrieNode* &Dic, string prefix){
    TrieNode* pTrie = Dic;
    for(int i = 0; i <  prefix.length(); i++){
        pTrie = pTrie->next[prefix[i] - 'a'];
        if(pTrie == nullptr){
            return vector<string>();
        }
    }
    vector<string> res;
    findAll(pTrie, res, prefix);
    return res;
}

void Remove(TrieNode* &Dic, string word){
    TrieNode* pTrie = Dic;
    for(int i = 0; i <  word.length(); i++){
        pTrie = pTrie->next[word[i] - 'a'];
    }
    pTrie->ID = 0;    
}

void destruct(TrieNode* &Dic){
    TrieNode* pTrie = Dic;
    for(int i = 0; i < SIZE; i++){
        pTrie = Dic->next[i];
        if(pTrie != nullptr) {
            destruct(pTrie);
        }
    }
    delete Dic;
}