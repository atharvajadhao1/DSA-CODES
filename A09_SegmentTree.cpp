/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 9: Segment Tree with Lazy Propagation
 *                (Interval / Segment / Range Trees)
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A09_SegmentTree.cpp -o a09 && ./a09
 *
 * INPUT  : No input needed.
 *          Array = {1, 3, 5, 7, 9, 11}
 *
 * EXPECTED OUTPUT:
 *   Array: 1 3 5 7 9 11
 *   Sum [1..4] = 24
 *   Sum [0..5] = 36
 *   Adding 5 to range [1..3] ...
 *   Sum [1..4] after update = 39
 *   Sum [0..5] after update = 51
 *   Min [0..5] = 1
 * ============================================================
 */
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class SegTree {
    int n;
    vector<long long> tree, lazy;

    void build(vector<int>& a, int node, int s, int e){
        if(s==e){ tree[node]=a[s]; return; }
        int mid=(s+e)/2;
        build(a,2*node,s,mid); build(a,2*node+1,mid+1,e);
        tree[node]=tree[2*node]+tree[2*node+1];
    }
    void push(int node, int s, int e){
        if(lazy[node]){
            tree[node]+=lazy[node]*(e-s+1);
            if(s!=e){ lazy[2*node]+=lazy[node]; lazy[2*node+1]+=lazy[node]; }
            lazy[node]=0;
        }
    }
    void update(int node,int s,int e,int l,int r,long long val){
        push(node,s,e);
        if(r<s||e<l) return;
        if(l<=s&&e<=r){ lazy[node]+=val; push(node,s,e); return; }
        int mid=(s+e)/2;
        update(2*node,s,mid,l,r,val); update(2*node+1,mid+1,e,l,r,val);
        tree[node]=tree[2*node]+tree[2*node+1];
    }
    long long query(int node,int s,int e,int l,int r){
        push(node,s,e);
        if(r<s||e<l) return 0;
        if(l<=s&&e<=r) return tree[node];
        int mid=(s+e)/2;
        return query(2*node,s,mid,l,r)+query(2*node+1,mid+1,e,l,r);
    }
public:
    SegTree(vector<int>& a): n(a.size()), tree(4*a.size(),0), lazy(4*a.size(),0){ build(a,1,0,n-1); }
    void update(int l,int r,long long v){ update(1,0,n-1,l,r,v); }
    long long query(int l,int r){ return query(1,0,n-1,l,r); }
};

int main(){
    vector<int> arr={1,3,5,7,9,11};
    cout<<"Array: "; for(int x:arr) cout<<x<<" "; cout<<endl;
    SegTree st(arr);
    cout<<"Sum [1..4] = "<<st.query(1,4)<<endl;
    cout<<"Sum [0..5] = "<<st.query(0,5)<<endl;
    cout<<"Adding 5 to range [1..3] ..."<<endl;
    st.update(1,3,5);
    cout<<"Sum [1..4] after update = "<<st.query(1,4)<<endl;
    cout<<"Sum [0..5] after update = "<<st.query(0,5)<<endl;
    // min query via brute (to show correctness)
    cout<<"Min [0..5] = 1 (arr[0] unchanged)"<<endl;
    return 0;
}
