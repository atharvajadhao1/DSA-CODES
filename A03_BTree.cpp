/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 3: B-Tree (minimum degree T=2, i.e. order-4)
 *                Insert, Traverse, Search
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A03_BTree.cpp -o a03 && ./a03
 *
 * INPUT  : No input needed.
 *          Keys inserted: 10 20 5 6 12 30 7 17
 *
 * EXPECTED OUTPUT:
 *   Inserted: 10
 *   Inserted: 20
 *   Inserted: 5
 *   Inserted: 6
 *   Inserted: 12
 *   Inserted: 30
 *   Inserted: 7
 *   Inserted: 17
 *
 *   B-Tree In-order traversal (sorted):
 *   5 6 7 10 12 17 20 30
 *
 *   Search  6 : Found
 *   Search 15 : Not Found
 * ============================================================
 */

#include <iostream>
using namespace std;

const int T = 2;   // minimum degree  →  each node holds 1..3 keys

struct BNode {
    int  keys[2*T - 1];
    BNode* children[2*T];
    int  n;         // current number of keys
    bool leaf;

    BNode(bool isLeaf) : n(0), leaf(isLeaf) {
        for (int i = 0; i < 2*T; i++) children[i] = nullptr;
    }

    void traverse() {
        int i;
        for (i = 0; i < n; i++) {
            if (!leaf) children[i]->traverse();
            cout << keys[i] << " ";
        }
        if (!leaf) children[i]->traverse();
    }

    BNode* search(int k) {
        int i = 0;
        while (i < n && k > keys[i]) i++;
        if (i < n && keys[i] == k) return this;
        if (leaf) return nullptr;
        return children[i]->search(k);
    }
};

class BTree {
    BNode* root;

    void splitChild(BNode* x, int i) {
        BNode* z = new BNode(x->children[i]->leaf);
        BNode* y = x->children[i];
        z->n = T - 1;

        for (int j = 0; j < T - 1; j++) z->keys[j] = y->keys[j + T];
        if (!y->leaf)
            for (int j = 0; j < T; j++) z->children[j] = y->children[j + T];
        y->n = T - 1;

        for (int j = x->n; j >= i + 1; j--) x->children[j + 1] = x->children[j];
        x->children[i + 1] = z;
        for (int j = x->n - 1; j >= i; j--) x->keys[j + 1] = x->keys[j];
        x->keys[i] = y->keys[T - 1];
        x->n++;
    }

    void insertNonFull(BNode* x, int k) {
        int i = x->n - 1;
        if (x->leaf) {
            while (i >= 0 && x->keys[i] > k) { x->keys[i + 1] = x->keys[i]; i--; }
            x->keys[i + 1] = k;
            x->n++;
        } else {
            while (i >= 0 && x->keys[i] > k) i--;
            if (x->children[i + 1]->n == 2 * T - 1) {
                splitChild(x, i + 1);
                if (x->keys[i + 1] < k) i++;
            }
            insertNonFull(x->children[i + 1], k);
        }
    }

public:
    BTree() : root(nullptr) {}

    void insert(int k) {
        if (!root) {
            root = new BNode(true);
            root->keys[0] = k;
            root->n = 1;
        } else {
            if (root->n == 2 * T - 1) {
                BNode* s = new BNode(false);
                s->children[0] = root;
                splitChild(s, 0);
                int i = (s->keys[0] < k) ? 1 : 0;
                insertNonFull(s->children[i], k);
                root = s;
            } else {
                insertNonFull(root, k);
            }
        }
    }

    void traverse() {
        if (root) { root->traverse(); cout << endl; }
    }

    bool search(int k) {
        return root ? (root->search(k) != nullptr) : false;
    }
};

int main() {
    BTree t;
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        t.insert(keys[i]);
        cout << "Inserted: " << keys[i] << endl;
    }

    cout << "\nB-Tree In-order traversal (sorted):\n";
    t.traverse();

    cout << "\nSearch  6 : " << (t.search(6)  ? "Found" : "Not Found") << endl;
    cout << "Search 15 : " << (t.search(15) ? "Found" : "Not Found") << endl;

    return 0;
}
