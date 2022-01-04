#include "RBTree.h"


int main() {
    RBNode* root;
    root = nullptr;
    Insert(root, 10);
    Insert(root, 20);
    Insert(root, 30);
    Insert(root, 40);
    Insert(root, 50);
    Insert(root, 25);
    Insert(root, 35);
    levelOrder(root);
    cout << endl;
    cout << lookUp(root, 25) << endl;
    Remove(root, 25);
    cout << lookUp(root, 25) << endl;
    levelOrder(root);
    cout << endl;
    deleteTree(root);
    return 0;
}