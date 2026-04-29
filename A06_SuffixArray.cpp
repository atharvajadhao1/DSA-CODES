/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 6: Suffix Trees – Suffix Array + Pattern Search
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A06_SuffixArray.cpp -o a06 && ./a06
 *
 * INPUT  : No input needed. Text = "banana"
 *
 * EXPECTED OUTPUT:
 *   Text: banana
 *   Suffix Array:
 *     sa[0] = 6  -->  $
 *     sa[1] = 5  -->  a$
 *     sa[2] = 3  -->  ana$
 *     sa[3] = 1  -->  anana$
 *     sa[4] = 0  -->  banana$
 *     sa[5] = 4  -->  na$
 *     sa[6] = 2  -->  nana$
 *   Pattern Search:
 *     'ana' : Found
 *     'ban' : Found
 *     'xyz' : Not Found
 *     'nan' : Found
 * ============================================================
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> buildSA(const string& s){
    int n=s.size();
    vector<int> sa(n), rank_(n), tmp(n);
    for(int i=0;i<n;i++){ sa[i]=i; rank_[i]=s[i]; }
    for(int gap=1;gap<n;gap<<=1){
        auto cmp=[&](int a,int b){
            if(rank_[a]!=rank_[b]) return rank_[a]<rank_[b];
            int ra=a+gap<n?rank_[a+gap]:-1;
            int rb=b+gap<n?rank_[b+gap]:-1;
            return ra<rb;
        };
        sort(sa.begin(),sa.end(),cmp);
        tmp[sa[0]]=0;
        for(int i=1;i<n;i++) tmp[sa[i]]=tmp[sa[i-1]]+(cmp(sa[i-1],sa[i])?1:0);
        rank_=tmp;
    }
    return sa;
}

bool searchPattern(const string& text, const string& pat, const vector<int>& sa){
    int lo=0, hi=(int)sa.size()-1;
    while(lo<=hi){
        int mid=(lo+hi)/2;
        string suf=text.substr(sa[mid], min((int)pat.size(),(int)text.size()-sa[mid]));
        if(suf==pat) return true;
        else if(suf<pat) lo=mid+1;
        else hi=mid-1;
    }
    return false;
}

int main(){
    string text="banana";
    string t2=text+"$";
    vector<int> sa=buildSA(t2);

    cout<<"Text: "<<text<<endl;
    cout<<"Suffix Array:"<<endl;
    for(int i=0;i<(int)sa.size();i++)
        cout<<"  sa["<<i<<"] = "<<sa[i]<<"  -->  "<<t2.substr(sa[i])<<endl;

    vector<string> patterns={"ana","ban","xyz","nan"};
    cout<<"Pattern Search:"<<endl;
    for(auto& p:patterns)
        cout<<"  '"<<p<<"' : "<<(searchPattern(text,p,sa)?"Found":"Not Found")<<endl;
    return 0;
}
