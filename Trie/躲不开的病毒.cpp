#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
struct node
{
    bool end;
    bool visit;
    node *pre;
    node *child[2];
    node()
    {
        memset(child, 0, sizeof(child));
        end = false;
        visit = false;
        pre = NULL;
        
    }
} tree[30001];
char s[30001];
int cnt = 1;
void insert(node* now)
{
    for (int i = 0; s[i]; i++)
    {
        int temp = s[i] - '0';
        if(now->child[temp] == NULL)
        {
            cnt++;
            now->child[temp] = tree + cnt;
        }
        now = now->child[temp];
    }
    now->end = true;
}
queue<node*> q;
void buildpre()
{
    tree[0].child[0] = tree + 1;
    tree[0].child[1] = tree + 1;
    tree[1].pre = tree;
    q.push(tree+1);
    while(!q.empty())
    {
        node *now = q.front();
        q.pop();
        for (int i = 0; i < 2; i++)
        {
            node *p = now->child[i];
            if(p)
            {
                node *pre = now->pre;
                while(pre->child[i] == NULL)
                {
                    pre = pre->pre;
                }
                p->pre = pre->child[i];
                if(p->pre->end)
                {
                    p->end = true;
                }
                q.push(p);
            }
        }
    }
}
int flag = 0;
bool travel(node *root, bool ans)
{
    if (ans || flag){
        flag = 1;
        return true;
    }
    if (root->end){
        return false;
    }
    if(root->visit){
        flag = 1;
        return true;
    }
    root->visit = true;
    bool ss[2] = {0, 0};
    for (int i = 0; i < 2; i++)
    {
        if(root->child[i]){
            ss[i] = travel(root->child[i], false);
        }
        else {
            node *m = root->pre;
            while(m->child[i] == NULL){
                m = m->pre;
            }
            ss[i] = travel(m->child[i], false);
        }
    }
    root->visit = false;
    ans = ss[0] || ss[1];
    return ans;
}
int main()
{
    int n;
    cin >> n;
    while(n--)
    {
        memset(s, 0, sizeof(s));
        cin >> s;
        insert(tree + 1);
    }
    buildpre();
    bool ans = travel(tree + 1, false);
    if(ans){
        cout << "TAK";
    }
    else{
        cout << "NIE";
    }
    return 0;
}
