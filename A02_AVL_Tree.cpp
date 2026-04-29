/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 2: AVL Tree – Insert, Search, Display
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A02_AVL_Tree.cpp -o a02 && ./a02
 *
 * INPUT  : No input needed.
 *          Keys inserted in order: 10 20 30 40 50 25
 *
 * EXPECTED OUTPUT:
 *   Inserted 10, root = 10
 *   Inserted 20, root = 10
 *   Inserted 30, root = 20   <-- LL rotation triggered
 *   Inserted 40, root = 20
 *   Inserted 50, root = 30   <-- RR rotation triggered
 *   Inserted 25, root = 30
 *
 *   In-order (key, height):
 *   10(h=1) 20(h=2) 25(h=1) 30(h=3) 40(h=2) 50(h=1)
 *
 *   Search 25 : Found
 *   Search 99 : Not Found
 * ============================================================
 */

#include <iostream>
#include <algorithm>
using namespace std;

struct AVLNode {
    int key, height;
    AVLNode *left, *right;
    AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int height(AVLNode* n) { return n ? n->height : 0; }

void updateHeight(AVLNode* n) {
    n->height = 1 + max(height(n->left), height(n->right));
}

int getBalance(AVLNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x  = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left  = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y  = x->right;
    AVLNode* T2 = y->left;
    y->left  = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* insert(AVLNode* node, int key) {
    if (!node) return new AVLNode(key);

    if      (key < node->key) node->left  = insert(node->left,  key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node;    // duplicate key

    updateHeight(node);
    int bal = getBalance(node);

    // LL
    if (bal > 1  && key < node->left->key)  return rotateRight(node);
    // RR
    if (bal < -1 && key > node->right->key) return rotateLeft(node);
    // LR
    if (bal > 1  && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // RL
    if (bal < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

bool search(AVLNode* root, int key) {
    if (!root) return false;
    if (key == root->key) return true;
    if (key < root->key)  return search(root->left,  key);
    return search(root->right, key);
}

void inorder(AVLNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << "(h=" << root->height << ") ";
    inorder(root->right);
}

int main() {
    AVLNode* root = nullptr;
    int keys[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
        cout << "Inserted " << keys[i] << ", root = " << root->key << endl;
    }

    cout << "\nIn-order (key, height):\n";
    inorder(root);
    cout << endl;

    cout << "\nSearch 25 : " << (search(root, 25) ? "Found" : "Not Found") << endl;
    cout << "Search 99 : " << (search(root, 99) ? "Found" : "Not Found") << endl;

    return 0;
}
