#include "Trie.h"
#define FILE_NAME "HW6-dic.txt"

int main(){
    TrieNode* Dictionary = new TrieNode;
    creatTrie(Dictionary, FILE_NAME);
    cout << "Tim tu abay: " << lookup(Dictionary, "abay") << endl;  //55. abay
    cout << "Tim tu igdrasil: " << lookup(Dictionary, "igdrasil") << endl;  //64334. igdrasil
    cout << "Tim tu noah: " << lookup(Dictionary, "noah") << endl;  //87591. noah
    cout << "Tim tu reins: " << lookup(Dictionary, "reins") << endl;  //107364. reins
    cout << "Tim tu spaces: " << lookup(Dictionary, "spaces") << endl;  //122484. spaces

    Insert(Dictionary, "abcdefu", 999999);
    cout << "Them va tim tu abcdefu: " << lookup(Dictionary, "abcdefu") << endl;  //999999
    Remove(Dictionary, "abcdefu");
    cout << "Xoa va tim tu abcdefu: " << lookup(Dictionary, "abcdefu") << endl;  //none = 0
    string prefix = "abc";
    vector<string> res = lookupPrefix(Dictionary, prefix);  // dag lam
    cout << "Tim tu bat dau bang " << prefix << ": " << endl;
    for(auto i : res)
        cout << i << " ";
    cout << endl;
    destruct(Dictionary);
}