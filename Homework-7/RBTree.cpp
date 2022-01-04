#include "RBtree.h"

RBNode* creatNode(int key) {
    RBNode *node = new RBNode;
    node->key = key;
    node->left = node->right = node->parent = nullptr;
    node->color = RED;
    return node;
}

bool isLeftNode(RBNode* node) { 
	return node == node->parent->left; 
}
RBNode *findSibling(RBNode* node) {
    if (node->parent == nullptr)
        return nullptr;
    if (isLeftNode(node))
        return node->parent->right;
    return node->parent->left;
}
RBNode *findUncle(RBNode* node) {
    if (node->parent == nullptr || node->parent->parent == nullptr)
        return nullptr;
    if (isLeftNode(node->parent))
        return node->parent->parent->right;
    else
        return node->parent->parent->left;
}
void moveDown(RBNode *nParent, RBNode* node) {
    if (node->parent != nullptr) {
        if (isLeftNode(node)) {
            node->parent->left = nParent;
        } else {
            node->parent->right = nParent;
        }
    }
    nParent->parent = node->parent;
    node->parent = nParent;
}
bool hasRedChild(RBNode* node) {
    return (left != nullptr && node->left->color == RED) || (right != nullptr && node->right->color == RED);
}

void leftRotate(RBNode *&pRoot, RBNode *node) {
    RBNode *nParent = node->right;
    if (node == pRoot)
        pRoot = nParent;
    moveDown(nParent, node);
    node->right = nParent->left;
    if (nParent->left != nullptr)
        nParent->left->parent = node;
    nParent->left = node;
}

void rightRotate(RBNode *&pRoot, RBNode *node) {
    RBNode *nParent = node->left;
    if (node == pRoot)
        pRoot = nParent;
    moveDown(nParent, node);
    node->left = nParent->right;
    if (nParent->right != nullptr)
        nParent->right->parent = node;
    nParent->right = node;
}
void swapColor(RBNode *node1, RBNode *node2) {
    bool temp;
    temp = node1->color;
    node1->color = node2->color;
    node2->color = temp;
}
void swapValues(RBNode *node1, RBNode *node2) {
    int temp;
    temp = node1->key;
    node1->key = node2->key;
    node2->key = temp;
}

// red red case
void fixRedRed(RBNode *&pRoot, RBNode *node) {
    if (node == pRoot) {
        node->color = BLACK;
        return;
    }
    RBNode *parent = node->parent, *grandparent = parent->parent,
         *uncle = findUncle(node);
    if (parent->color != BLACK) {
        if (uncle != nullptr && uncle->color == RED) {
            parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            fixRedRed(pRoot, grandparent);
        } else {
            if (isLeftNode(parent)) {
                if (isLeftNode(node)) {
                    swapColor(parent, grandparent);
                } else {
                    leftRotate(pRoot, parent);
                    swapColor(node, grandparent);
                }
                rightRotate(pRoot, grandparent);
            } else {
                if (isLeftNode(node)) {
                    rightRotate(pRoot, parent);
                    swapColor(node, grandparent);
                } else {
                    swapColor(parent, grandparent);
                }
                leftRotate(pRoot, grandparent);
            }
        }
    }
}
RBNode *mostLeftNode(RBNode *node) {
    RBNode *temp = node;
    while (temp->left != nullptr)
        temp = temp->left;
    return temp;
}
RBNode *findReplace(RBNode *node) {
    if (node->left != nullptr && node->right != nullptr)
        return mostLeftNode(node->right);
    if (node->left == nullptr && node->right == nullptr)
        return nullptr;
    if (node->left != nullptr)
        return node->left;
    else
        return node->right;
}
void deleteNode(RBNode *&pRoot, RBNode *&node) {
    RBNode *tmp = findReplace(node);
    bool isBlack = ((tmp == nullptr || tmp->color == BLACK) && (node->color == BLACK));
    RBNode *parent = node->parent;
    if (tmp == nullptr) {
        if (node == pRoot) {
            pRoot = nullptr;
        } else {
            if (isBlack) {
                fixDoubleBlack(pRoot, node);
            } else {
                if (findSibling(node) != nullptr)
                    findSibling(node)->color = RED;
            }
            if (isLeftNode(node)) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
        delete node;
        node = nullptr;
        return;
    }
    if (node->left == nullptr || node->right == nullptr) {
        if (node == pRoot) {
            node->key = tmp->key;
            node->left = node->right = nullptr;
            delete tmp;
            tmp = nullptr;
        } else {
            if (isLeftNode(node)) {
                parent->left = tmp;
            } else {
                parent->right = tmp;
            }
            delete node;
            node = nullptr;
            tmp->parent = parent;
            if (isBlack) {
                fixDoubleBlack(pRoot, tmp);
            } else {
                tmp->color = BLACK;
            }
        }
        return;
    }
    swapValues(tmp, node);
    deleteNode(pRoot, tmp);
}

// double black case
void fixDoubleBlack(RBNode *&pRoot, RBNode *node) {
    if (node == pRoot)
        return;
    RBNode *sibling = findSibling(node), *parent = node->parent;
    if (sibling == nullptr) {
        fixDoubleBlack(pRoot, parent);
    } else {
        if (sibling->color == RED) {
            parent->color = RED;
            sibling->color = BLACK;
            if (isLeftNode(sibling)) {
                rightRotate(pRoot, parent);
            } else {
                leftRotate(pRoot, parent);
            }
            fixDoubleBlack(pRoot, node);
        } else {
            if (hasRedChild(sibling)) {
                if (sibling->left != nullptr && sibling->left->color == RED) {
                    if (isLeftNode(sibling)) {
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rightRotate(pRoot, parent);
                    } else {
                        sibling->left->color = parent->color;
                        rightRotate(pRoot, sibling);
                        leftRotate(pRoot, parent);
                    }
                } else {
                    if (isLeftNode(sibling)) {
                        sibling->right->color = parent->color;
                        leftRotate(pRoot, sibling);
                        rightRotate(pRoot, parent);
                    } else {
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        leftRotate(pRoot, parent);
                    }
                }
                parent->color = BLACK;
            } else {
                sibling->color = RED;
                if (parent->color == BLACK)
                    fixDoubleBlack(pRoot, parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}
void levelOrder(RBNode *node) {
    if (node == nullptr)
        return;
    queue<RBNode *> q;
    RBNode *curr;
    q.push(node);
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        cout << curr->key << " ";
        if (curr->left != nullptr)
            q.push(curr->left);
        if (curr->right != nullptr)
            q.push(curr->right);
    }
}
void inOrder(RBNode *node) {
    if (node == nullptr)
        return;
    inOrder(node->left);
    cout << node->key << " ";
    inOrder(node->right);
}
RBNode *searchNode(RBNode *&pRoot, int n) {
    RBNode *temp = pRoot;
    while (temp != nullptr) {
        if (n < temp->key) {
            if (temp->left == nullptr)
                break;
            else
                temp = temp->left;
        } else if (n == temp->key) {
            break;
        } else {
            if (temp->right == nullptr)
                break;
            else
                temp = temp->right;
        }
    }
    return temp;
}
RBNode* lookUp(RBNode* pRoot, int key) {
    RBNode* res = searchNode(pRoot, key);
    if (res && res->key == key)
        return res;
    return nullptr;
}
void Insert(RBNode *&pRoot, int key) {
    RBNode *newNode = creatNode(key);
    if (pRoot == nullptr) {
        newNode->color = BLACK;
        pRoot = newNode;
    } else {
        RBNode *temp = searchNode(pRoot, key);
        if (temp->key == key) {
            cout << "Key has been appeared" << endl;
            return;
        }
        newNode->parent = temp;
        if (key < temp->key)
            temp->left = newNode;
        else
            temp->right = newNode;
        fixRedRed(pRoot, newNode);
    }
}
void Remove(RBNode *&pRoot, int key) {
    if (pRoot == nullptr)
        return;
    RBNode *node = searchNode(pRoot, key), *u;
    if (node->key != key) {
        cout << "Not found!" << endl;
        return;
    }
    deleteNode(pRoot, node);
}
int Height(RBNode *pRoot) {
    if (pRoot == nullptr)
        return 0;
    return 1 + max(Height(pRoot->left), Height(pRoot->right));
}
int BlackHeight(RBNode* pRoot) {
    if (pRoot == nullptr)
        return 0;
    if (pRoot->color == BLACK)
        return 1 + BlackHeight(pRoot->left);
    return BlackHeight(pRoot->left);
}
RBNode* createTree(int a[], int n) {
    RBNode *pRoot = nullptr;
    for (int i = 0; i < n; i++) 
        Insert(pRoot, a[i]);
    return pRoot;
}
    
void deleteTree(RBNode* &pRoot){
    if(pRoot == nullptr)
        return;
    else{
        deleteTree(pRoot->left);
        deleteTree(pRoot->right);
    }
    delete pRoot;
}
