/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 13: Succinct Data Structures – Bit Vector Rank/Select
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A13_SuccinctBitVector.cpp -o a13 && ./a13
 *
 * INPUT  : No input needed.
 *          Bit vector = "1011010011010110"
 *
 * EXPECTED OUTPUT:
 *   Bit Vector : 1011010011010110
 *   Length     : 16 bits
 *   Total 1s   : 9
 *
 *   Rank queries (number of 1s in bits[0..i]):
 *   rank1(0)  = 1    rank0(0)  = 0
 *   rank1(3)  = 3    rank0(3)  = 1
 *   rank1(7)  = 4    rank0(7)  = 4
 *   rank1(10) = 6    rank0(10) = 5
 *   rank1(15) = 9    rank0(15) = 7
 *
 *   Select queries (position of j-th 1):
 *   select1(1) = 0
 *   select1(2) = 2
 *   select1(3) = 3
 *   select1(5) = 8
 *   select1(8) = 13
 * ============================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
using namespace std;

class BitVector {
    vector<uint64_t> words;
    vector<int> blockRank;
    int n;
    int popcount(uint64_t x){ return __builtin_popcountll(x); }
public:
    BitVector(const string& bits): n(bits.size()){
        int nw=(n+63)/64;
        words.resize(nw,0);
        for(int i=0;i<n;i++) if(bits[i]=='1') words[i/64]|=(1ULL<<(i%64));
        blockRank.resize(nw+1,0);
        for(int i=0;i<nw;i++) blockRank[i+1]=blockRank[i]+popcount(words[i]);
    }
    int rank1(int i){
        int blk=i/64, bit=i%64;
        uint64_t mask=(bit==63)?~0ULL:(1ULL<<(bit+1))-1;
        return blockRank[blk]+popcount(words[blk]&mask);
    }
    int rank0(int i){ return (i+1)-rank1(i); }
    int select1(int j){
        for(int i=0;i<n;i++) if(((words[i/64]>>(i%64))&1)&&--j==0) return i;
        return -1;
    }
    int total1(){ return rank1(n-1); }
    int size(){ return n; }
};

int main(){
    string bits="1011010011010110";
    BitVector bv(bits);
    cout<<"Bit Vector : "<<bits<<endl;
    cout<<"Length     : "<<bv.size()<<" bits"<<endl;
    cout<<"Total 1s   : "<<bv.total1()<<endl;

    cout<<"\nRank queries (number of 1s in bits[0..i]):"<<endl;
    for(int i:{0,3,7,10,15})
        cout<<"rank1("<<i<<")  = "<<bv.rank1(i)<<"    rank0("<<i<<")  = "<<bv.rank0(i)<<endl;

    cout<<"\nSelect queries (position of j-th 1):"<<endl;
    for(int j:{1,2,3,5,8})
        cout<<"select1("<<j<<") = "<<bv.select1(j)<<endl;
    return 0;
}
