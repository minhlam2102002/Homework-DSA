#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Tokenizer.h"
#define SIZE 26
#define SEP ". "
using namespace std;

struct TrieNode{
    int ID;
    TrieNode* next[SIZE] = {nullptr};
};

void Insert(TrieNode* &Dic, string word, int id);
void creatTrie(TrieNode* &Dic, string DicFile);
int lookup(TrieNode* &Dic, string word);
vector<string> lookupPrefix(TrieNode* &Dic, string prefix);
void Remove(TrieNode* &Dic, string word);
void destruct(TrieNode* &Dic);