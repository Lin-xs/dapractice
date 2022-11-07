/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-10-23 21:39:14
 * @LastEditTime: 2022-10-23 22:11:17
 * @LastEditors: Linxs
 */
#include<iostream>
#include<deque>
#include<cstring>
#include<algorithm>
using namespace std;
int nums = 0;
const int letters = 26;
char s[2000];
struct node
{
    node *childs[letters];
    node *pre;
    bool badnode;
    node(){
        memset(childs, 0, sizeof(childs));
        pre = NULL;
        badnode = false;
    }
} tree[140000];
void insert(node* now)
{
    for (int i = 0; s[i]; i++)
    {
        if(now->childs[s[i] - 'a'] == NULL)
        {
            now->childs[s[i] - 'a'] = tree + nums;
            nums++;
        }
        now = now->childs[s[i] - 'a'];
    }
    now->badnode = 1;
}
void build_dfa()
{
    for (int i = 0; i < letters;i++){
        tree[0].childs[i] = tree + 1;
    }
    tree[0].pre = NULL;
    tree[1].pre = tree;
    deque<node *> q;
    q.push_back(tree + 1);
    while(!q.empty()){
        node *now = q.front();
        q.pop_front();
        for (int i = 0; i < letters;i++){
            node *p = now->childs[i];
            if(p){
                node *pre = now->pre;
                while(pre->childs[i]==NULL){
                    pre = pre->pre;
                }
                p->pre = pre->childs[i];
                if(pre->badnode)
                    p->badnode = true;
                q.push_back(p);
            }
        }
    }
}
bool find_dfa(){
    node *j = tree + 1;
    for (int i = 0; s[i];i++)
    {
        
        int k = s[i] - 'a';
        while(j->childs[k]==NULL){
            j = j->pre;
        }
        j = j->childs[k];
        if(j->badnode){
            return true;
        }
    }
    return false;
}
int main()
{
    int t;
    cin >> t;
    nums = 2;
    while(t--){
        memset(s, 0, sizeof(s));
        cin >> s;
        insert(tree + 1);
    }
    build_dfa();
    cin >> t;
    while(t--){
        memset(s, 0, sizeof(s));
        cin >> s;
        if(find_dfa()){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
    return 0;
}
