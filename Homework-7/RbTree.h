#include <iostream>
#include <queue>
using namespace std;
const bool RED = true;
const bool BLACK = false;

struct RBNode {
    int key;
    bool color;  // Black = 0
    RBNode *parent, *left, *right;
};

RBNode* creatNode(int key);
bool isLeftNode(RBNode* node);
RBNode *findSibling(RBNode* node);
RBNode *findUncle(RBNode* node);
void moveDown(RBNode *nParent, RBNode* node);
bool hasRedChild(RBNode* node);

void leftRotate(RBNode *&pRoot, RBNode* node);
void rightRotate(RBNode *&pRoot, RBNode *node);
void swapColor(RBNode *node1, RBNode *node2);
void swapValues(RBNode *node1, RBNode *node2);
void fixRedRed(RBNode *&pRoot, RBNode *node);
RBNode *mostLeftNode(RBNode *node);
RBNode *findReplace(RBNode *node);
void deleteNode(RBNode *&pRoot, RBNode *&node);
void fixDoubleBlack(RBNode *&pRoot, RBNode *node);
void levelOrder(RBNode *node);
void inOrder(RBNode *node);
RBNode *searchNode(RBNode *&pRoot, int key);
void Insert(RBNode *&pRoot, int key);
RBNode* createTree(int a[], int n);
RBNode* lookUp(RBNode* pRoot, int key);
int Height(RBNode *pRoot);
int BlackHeight(RBNode* pRoot);
void Remove(RBNode *&pRoot, int key);
void deleteTree(RBNode* &pRoot);