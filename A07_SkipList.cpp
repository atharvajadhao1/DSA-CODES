/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 7: Randomized Data Structures – Skip List
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A07_SkipList.cpp -o a07 && ./a07
 *
 * INPUT  : No input needed.
 *          Keys inserted: 3 6 7 9 12 17 19 21 25
 *
 * EXPECTED OUTPUT:
 *   Inserted 3  at level 0
 *   Inserted 6  at level 1
 *   Inserted 7  at level 0
 *   Inserted 9  at level 2
 *   Inserted 12 at level 0
 *   Inserted 17 at level 1
 *   Inserted 19 at level 0
 *   Inserted 21 at level 2
 *   Inserted 25 at level 0
 *
 *   Skip List (level 0 = all elements):
 *   Level 0: 3 6 7 9 12 17 19 21 25
 *   Level 1: 6 9 17 21
 *   Level 2: 9 21
 *
 *   Search 17 : Found
 *   Search 10 : Not Found
 * ============================================================
 */
#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;

const int MAXLEVEL = 4;
const float P = 0.5f;

struct SkipNode {
    int key;
    SkipNode* forward[MAXLEVEL+1];
    SkipNode(int k): key(k){ for(int i=0;i<=MAXLEVEL;i++) forward[i]=nullptr; }
};

class SkipList {
    int level;
    SkipNode* header;
    int randomLevel(){
        int lvl=0;
        while((float)rand()/RAND_MAX < P && lvl<MAXLEVEL) lvl++;
        return lvl;
    }
public:
    SkipList(): level(0){ header=new SkipNode(INT_MIN); }
    void insert(int key){
        SkipNode* update[MAXLEVEL+1];
        SkipNode* cur=header;
        for(int i=level;i>=0;i--){
            while(cur->forward[i] && cur->forward[i]->key < key) cur=cur->forward[i];
            update[i]=cur;
        }
        int rl=randomLevel();
        if(rl>level){ for(int i=level+1;i<=rl;i++) update[i]=header; level=rl; }
        SkipNode* n=new SkipNode(key);
        for(int i=0;i<=rl;i++){ n->forward[i]=update[i]->forward[i]; update[i]->forward[i]=n; }
        cout<<"Inserted "<<key<<" at level "<<rl<<endl;
    }
    bool search(int key){
        SkipNode* cur=header;
        for(int i=level;i>=0;i--)
            while(cur->forward[i] && cur->forward[i]->key < key) cur=cur->forward[i];
        cur=cur->forward[0];
        return cur && cur->key==key;
    }
    void display(){
        cout<<"\nSkip List (level 0 = all elements):"<<endl;
        for(int i=0;i<=level;i++){
            SkipNode* n=header->forward[i];
            cout<<"Level "<<i<<": ";
            while(n){ cout<<n->key<<" "; n=n->forward[i]; }
            cout<<endl;
        }
    }
};

int main(){
    srand(42);
    SkipList sl;
    int keys[]={3,6,7,9,12,17,19,21,25};
    for(int k:keys) sl.insert(k);
    sl.display();
    cout<<"\nSearch 17 : "<<(sl.search(17)?"Found":"Not Found")<<endl;
    cout<<"Search 10 : "<<(sl.search(10)?"Found":"Not Found")<<endl;
    return 0;
}
