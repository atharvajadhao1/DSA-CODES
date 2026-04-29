/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 5: Trie – Insert, Search, Auto-complete
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A05_Trie.cpp -o a05 && ./a05
 *
 * INPUT  : No input needed.
 *
 * EXPECTED OUTPUT:
 *   Inserted: apple app application apt bat ball band
 *   search('app')   : Found
 *   search('apply') : Not Found
 *   Suggestions for 'ap': app apple application apt
 *   Suggestions for 'ba': ball band bat
 * ============================================================
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TrieNode {
    TrieNode* ch[26];
    bool isEnd;
    TrieNode() : isEnd(false) { for(int i=0;i<26;i++) ch[i]=nullptr; }
};

class Trie {
    TrieNode* root;
    void collect(TrieNode* n, string cur, vector<string>& res) {
        if(n->isEnd) res.push_back(cur);
        for(int i=0;i<26;i++)
            if(n->ch[i]) collect(n->ch[i], cur+(char)('a'+i), res);
    }
public:
    Trie() { root = new TrieNode(); }
    void insert(const string& w) {
        TrieNode* c=root;
        for(char x:w){ int i=x-'a'; if(!c->ch[i]) c->ch[i]=new TrieNode(); c=c->ch[i]; }
        c->isEnd=true;
    }
    bool search(const string& w) {
        TrieNode* c=root;
        for(char x:w){ int i=x-'a'; if(!c->ch[i]) return false; c=c->ch[i]; }
        return c->isEnd;
    }
    void autocomplete(const string& prefix) {
        TrieNode* c=root;
        for(char x:prefix){ int i=x-'a'; if(!c->ch[i]){ cout<<"No suggestions for '"<<prefix<<"'\n"; return; } c=c->ch[i]; }
        vector<string> res; collect(c, prefix, res);
        cout<<"Suggestions for '"<<prefix<<"': ";
        for(auto& s:res) cout<<s<<" "; cout<<endl;
    }
};

int main(){
    Trie t;
    vector<string> words={"apple","app","application","apt","bat","ball","band"};
    cout<<"Inserted: ";
    for(auto& w:words){ t.insert(w); cout<<w<<" "; } cout<<"\n\n";
    cout<<"search('app')   : "<<(t.search("app")?"Found":"Not Found")<<endl;
    cout<<"search('apply') : "<<(t.search("apply")?"Found":"Not Found")<<endl<<endl;
    t.autocomplete("ap");
    t.autocomplete("ba");
    return 0;
}
