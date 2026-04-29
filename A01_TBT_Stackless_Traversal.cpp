/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 1: Threaded Binary Tree (TBT) - Stackless Traversal
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A01_TBT_Stackless_Traversal.cpp -o a01 && ./a01
 *
 * INPUT  : No input needed – tree is built with hardcoded keys.
 *          Keys inserted: 20 10 30 5 15 25 35
 *
 * EXPECTED OUTPUT:
 *   Inserting keys: 20 10 30 5 15 25 35
 *   In-order traversal (TBT, no stack): 5 10 15 20 25 30 35
 * ============================================================
 */

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    bool rightThread;  // true  -> right pointer is a thread (points to in-order successor)
    bool leftThread;   // true  -> left  pointer is a thread (points to in-order predecessor)
};

Node* newNode(int data) {
    Node* n    = new Node();
    n->data    = data;
    n->left    = nullptr;
    n->right   = nullptr;
    n->rightThread = false;
    n->leftThread  = false;
    return n;
}

/* Insert into a fully-threaded BST */
Node* insert(Node* root, int key) {
    Node* ptr = root;
    Node* par = nullptr;

    while (ptr != nullptr) {
        if (key == ptr->data) return root;   // duplicate
        par = ptr;
        if (key < ptr->data) {
            if (!ptr->leftThread) ptr = ptr->left;
            else break;
        } else {
            if (!ptr->rightThread) ptr = ptr->right;
            else break;
        }
    }

    Node* tmp = newNode(key);

    if (par == nullptr) {           // tree was empty
        root = tmp;
        tmp->leftThread  = true;
        tmp->rightThread = true;
        tmp->left  = nullptr;
        tmp->right = nullptr;
    } else if (key < par->data) {   // insert as left child
        tmp->left        = par->left;
        tmp->right       = par;
        tmp->leftThread  = par->leftThread;
        tmp->rightThread = true;
        par->leftThread  = false;
        par->left        = tmp;
    } else {                        // insert as right child
        tmp->left        = par;
        tmp->right       = par->right;
        tmp->leftThread  = true;
        tmp->rightThread = par->rightThread;
        par->rightThread = false;
        par->right       = tmp;
    }
    return root;
}

/* In-order traversal using threads — O(1) space, no stack */
void inorder(Node* root) {
    if (!root) { cout << "(empty tree)" << endl; return; }

    Node* cur = root;
    // Go to the left-most node
    while (!cur->leftThread)
        cur = cur->left;

    while (cur) {
        cout << cur->data << " ";
        if (cur->rightThread)
            cur = cur->right;          // follow thread to in-order successor
        else {
            cur = cur->right;
            while (cur && !cur->leftThread)
                cur = cur->left;
        }
    }
    cout << endl;
}

int main() {
    Node* root = nullptr;
    int keys[] = {20, 10, 30, 5, 15, 25, 35};
    int n = sizeof(keys) / sizeof(keys[0]);

    cout << "Inserting keys: ";
    for (int i = 0; i < n; i++) {
        cout << keys[i] << " ";
        root = insert(root, keys[i]);
    }
    cout << endl;

    cout << "In-order traversal (TBT, no stack): ";
    inorder(root);

    return 0;
}
