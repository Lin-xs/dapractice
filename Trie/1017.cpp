#include<string>
using namespace std;

struct trienode{
    trienode* child[26];
    trienode(){
        memset(child, 0, sizeof(child));
    }
};

void build(string s, trienode* root){
    trienode* p = root;
    for(int i = 0; i < s.size(); i++){
        if(p->child[s[i]-'a'] == NULL)
            p->child[s[i]-'a'] = new trienode();
        p = p->child[s[i]-'a'];
    }
}







