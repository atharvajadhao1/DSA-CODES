/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 11: Disjoint Set (Union-Find) – Cycle Detection
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A11_DisjointSet.cpp -o a11 && ./a11
 *
 * INPUT  : No input needed.
 *          Graph edges: (0-1)(1-2)(2-3)(3-4)(4-5)(3-1)
 *
 * EXPECTED OUTPUT:
 *   Processing edges:
 *   Edge (0-1) : Added
 *   Edge (1-2) : Added
 *   Edge (2-3) : Added
 *   Edge (3-4) : Added
 *   Edge (4-5) : Added
 *   Edge (3-1) : CYCLE DETECTED!
 *
 *   Connectivity:
 *   0 and 5 connected? Yes
 *   0 and 3 connected? Yes
 * ============================================================
 */
#include <iostream>
#include <vector>
using namespace std;

class DSU {
    vector<int> parent, rank_;
public:
    DSU(int n): parent(n), rank_(n,0){ for(int i=0;i<n;i++) parent[i]=i; }
    int find(int x){ if(parent[x]!=x) parent[x]=find(parent[x]); return parent[x]; }
    bool unite(int x,int y){
        int px=find(x), py=find(y);
        if(px==py) return false;
        if(rank_[px]<rank_[py]) swap(px,py);
        parent[py]=px;
        if(rank_[px]==rank_[py]) rank_[px]++;
        return true;
    }
    bool connected(int x,int y){ return find(x)==find(y); }
};

int main(){
    DSU dsu(6);
    vector<pair<int,int>> edges={{0,1},{1,2},{2,3},{3,4},{4,5},{3,1}};
    cout<<"Processing edges:"<<endl;
    for(auto [u,v]:edges){
        bool ok=dsu.unite(u,v);
        cout<<"Edge ("<<u<<"-"<<v<<") : "<<(ok?"Added":"CYCLE DETECTED!")<<endl;
    }
    cout<<"\nConnectivity:"<<endl;
    cout<<"0 and 5 connected? "<<(dsu.connected(0,5)?"Yes":"No")<<endl;
    cout<<"0 and 3 connected? "<<(dsu.connected(0,3)?"Yes":"No")<<endl;
    return 0;
}
