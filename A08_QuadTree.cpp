/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 8: Quad Tree – 2D Spatial Indexing & Range Query
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A08_QuadTree.cpp -o a08 && ./a08
 *
 * INPUT  : No input needed.
 *
 * EXPECTED OUTPUT:
 *   Inserted: A (10,10)
 *   Inserted: B (20,80)
 *   Inserted: C (75,25)
 *   Inserted: D (50,50)
 *   Inserted: E (60,70)
 *   Inserted: F (15,40)
 *
 *   Points in region (0,0)-(50,50):
 *     A (10,10)
 *     F (15,40)
 *     D (50,50)
 *
 *   Points in region (50,50)-(100,100):
 *     D (50,50)
 *     E (60,70)
 * ============================================================
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Point { float x, y; string name; };

struct Rect {
    float x, y, w, h;
    bool contains(const Point& p) const { return p.x>=x && p.x<=x+w && p.y>=y && p.y<=y+h; }
    bool intersects(const Rect& o) const { return !(o.x>x+w||o.x+o.w<x||o.y>y+h||o.y+o.h<y); }
};

class QuadTree {
    static const int CAP = 4;
    Rect boundary;
    vector<Point> points;
    QuadTree *nw,*ne,*sw,*se;
    bool divided;
    void subdivide(){
        float hw=boundary.w/2, hh=boundary.h/2;
        nw=new QuadTree({boundary.x,      boundary.y,      hw, hh});
        ne=new QuadTree({boundary.x+hw,   boundary.y,      hw, hh});
        sw=new QuadTree({boundary.x,      boundary.y+hh,   hw, hh});
        se=new QuadTree({boundary.x+hw,   boundary.y+hh,   hw, hh});
        divided=true;
    }
public:
    QuadTree(Rect b): boundary(b), nw(nullptr),ne(nullptr),sw(nullptr),se(nullptr),divided(false){}
    bool insert(const Point& p){
        if(!boundary.contains(p)) return false;
        if((int)points.size()<CAP && !divided){ points.push_back(p); return true; }
        if(!divided) subdivide();
        return nw->insert(p)||ne->insert(p)||sw->insert(p)||se->insert(p);
    }
    void query(const Rect& r, vector<Point>& found) const {
        if(!boundary.intersects(r)) return;
        for(auto& p:points) if(r.contains(p)) found.push_back(p);
        if(divided){ nw->query(r,found); ne->query(r,found); sw->query(r,found); se->query(r,found); }
    }
};

int main(){
    QuadTree qt({0,0,100,100});
    vector<Point> pts;
    pts.push_back({10,10,"A"}); pts.push_back({20,80,"B"}); pts.push_back({75,25,"C"});
    pts.push_back({50,50,"D"}); pts.push_back({60,70,"E"}); pts.push_back({15,40,"F"});
    for(auto& p:pts){ qt.insert(p); cout<<"Inserted: "<<p.name<<" ("<<p.x<<","<<p.y<<")"<<endl; }

    auto printQuery=[&](Rect r, string label){
        vector<Point> res; qt.query(r,res);
        cout<<"\nPoints in region "<<label<<":"<<endl;
        for(auto& p:res) cout<<"  "<<p.name<<" ("<<p.x<<","<<p.y<<")"<<endl;
    };
    printQuery({0,0,50,50},  "(0,0)-(50,50)");
    printQuery({50,50,50,50},"(50,50)-(100,100)");
    return 0;
}
