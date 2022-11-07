#include <iostream>
#include <string.h>
#include <algorithm>
#include <stack>
#include <string>
#include <math.h>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <set>

using namespace std;
const int maxn = 30005;
int n, nodecou;
char virus[maxn];
int nums = 2;
// bool instack[maxn];

struct node {
    node* next[2];
    int prev;
    bool isdanger;
    bool visit;
    node() {
        memset(next, 0, sizeof(next));
        prev = NULL;
        isdanger = false;
        visit = false;
    }
}tree[maxn];

void insert() {
    int now = 1, l = strlen(virus);
    for (int i = 0; i < l; i++) {
        int idx = virus[i] - '0';
        if (tree[now].next[idx] == 0) {
            nodecou++;
            tree[now].next[idx] = nodecou;
        }
        now = tree[now].next[idx];
        if (i == l - 1)
            tree[now].isdanger = true;
    }
}

void insert(node* now)
{
    for (int i = 0; virus[i]; i++)
    {
        if(now->next[virus[i] - 'a'] == NULL)
        {
            now->next[virus[i] - 'a'] = tree + nums;
            nums++;
        }
        now = now->next[virus[i] - 'a'];
    }
    now->isdanger = 1;
}

void build() {
    tree[0].next[0] = tree + 1, tree[0].next[1] = tree + 1;
    tree[1].prev = 0;
    queue<int>q;
    q.push(1);
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (int i = 0; i < 2; i++) {
            int child = tree[now].next[i];
            int prev = tree[now].prev;
            if (child) {
                while (tree[prev].next[i] == NULL)
                    prev = tree[prev].prev;
                tree[child].prev = tree[prev].next[i];
                if (tree[tree[child].prev].isdanger)
                    tree[child].isdanger = true;
                q.push(child);
            }
            else {
                while (!tree[prev].next[i])
                    prev = tree[prev].prev;
                tree[now].next[i] = tree[prev].next[i];
                if (tree[child].isdanger)
                    tree[now].next[i] = 0;
            }
        }
    }
}

bool dfs(node* rt) {
    if (rt->visit)return true;
    rt->visit = true;
    bool ans = false;
    for (int i = 0; i < 2; i++)
        if (rt->next[i] && !tree[rt->next[i]].isdanger)
        {
            ans = ans || dfs(tree + rt->next[i]);
            if (ans)return true;
        }
    rt->visit = false;
    return false;
}

void init() {
    scanf("%d", &n);
    nodecou = 1;
    while (n--) {
        scanf("%s", virus);
        insert();
    }
    build();
    if (dfs(tree+1))
        printf("TAK\n");
    else
        printf("NIE\n");
}

int main()
{
    init();
    return 0;
}