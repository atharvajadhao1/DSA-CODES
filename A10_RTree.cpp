/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 10: R-Tree – Spatial Indexing via MBR Overlap
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A10_RTree.cpp -o a10 && ./a10
 *
 * INPUT  : No input needed.
 *
 * EXPECTED OUTPUT:
 *   Inserted: Park     [0,0 - 10,10]
 *   Inserted: Mall     [5,5 - 20,20]
 *   Inserted: Hospital [15,0 - 30,15]
 *   Inserted: School   [25,10 - 40,25]
 *   Inserted: Lake     [0,15 - 12,30]
 *
 *   Search [4,4 - 18,18]:
 *     -> Park     (area=100)
 *     -> Mall     (area=225)
 *     -> Hospital (area=225)
 *     -> Lake     (area=180)
 *
 *   Search [20,20 - 45,45]:
 *     -> Mall   (area=225)
 *     -> School (area=225)
 * ============================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct MBR {
    float minX,minY,maxX,maxY;
    string label;
    bool overlaps(const MBR& o) const {
        return !(o.minX>maxX||o.maxX<minX||o.minY>maxY||o.maxY<minY);
    }
    float area() const { return (maxX-minX)*(maxY-minY); }
};

class RTree {
    vector<MBR> entries;
public:
    void insert(const MBR& m){
        entries.push_back(m);
        cout<<"Inserted: "<<left<<setw(12)<<m.label
            <<"["<<m.minX<<","<<m.minY<<" - "<<m.maxX<<","<<m.maxY<<"]"<<endl;
    }
    void search(const MBR& q) const {
        cout<<"\nSearch ["<<q.minX<<","<<q.minY<<" - "<<q.maxX<<","<<q.maxY<<"]:"<<endl;
        bool found=false;
        for(auto& e:entries)
            if(e.overlaps(q)){ cout<<"  -> "<<left<<setw(10)<<e.label<<"(area="<<e.area()<<")"<<endl; found=true; }
        if(!found) cout<<"  None"<<endl;
    }
};

int main(){
    RTree rt;
    rt.insert({0,0,10,10,   "Park"});
    rt.insert({5,5,20,20,   "Mall"});
    rt.insert({15,0,30,15,  "Hospital"});
    rt.insert({25,10,40,25, "School"});
    rt.insert({0,15,12,30,  "Lake"});
    rt.search({4,4,18,18});
    rt.search({20,20,45,45});
    return 0;
}
