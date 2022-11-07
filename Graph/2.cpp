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

const int maxn = 1005;
vector<vector<int>>G(maxn);
vector<set<int>>DAG(maxn);
int to[maxn], dfn[maxn], low[maxn],father[maxn],colorP[maxn];
bool route[maxn];
int ncount = 1, n, m, color;
stack<int>p;

void tarjan(int u,int father) {
    route[u] = true;
    p.push(u);
    low[u] = dfn[u] = ncount++;
    int l = G[u].size();
    for (int i = 0; i < l; i++) {
        int next = G[u][i];
        if (!dfn[next])
            tarjan(next, u);
        else if(route[next])
            low[u] = min(low[u], low[next]);
    }
    if (dfn[u] == low[u]) {
        int v = 0;
        ++color;
        while (v != u) {
            v = p.top();
            p.pop();
            colorP[v] = color;
        }
    }
    route[u] = false;
}

bool top() {
        int id, sum = 0;
        for (int i = 1; i <= color; i++) {
            if (to[i] == 0) {
                id = i;
                sum++;
            }
        }
        while (sum!=0)
        {
            if (sum > 1)
                return false;
            sum = 0;
            set<int>::iterator i1 = DAG[id].begin(), i2 = DAG[id].end();
            for (; i1 != i2; i1++)
            {
                to[*i1]--;
                if (to[*i1] == 0) {
                    id = *i1;
                    sum++;
                }
            }
        }
        return true;
}

void calculate() {
    for (int i = 1; i <= n; i++) {
        int size = G[i].size();
        for (int j = 0; j < size; j++) {
            int v = G[i][j];
            if (colorP[v] != colorP[i])
            {
                DAG[i].insert(colorP[v]);
                to[colorP[v]]++;
            }
        }
    }
    if (top())
        printf("Yes\n");
    else
        printf("No\n");
}

void init() {
    int kase;
    scanf("%d", &kase);
    while (kase--)
    {
        ncount = 1,n=0,m=0,color=0;
        memset(to, 0, sizeof(to));
        memset(dfn, 0, sizeof(to));
        memset(low, 0, sizeof(to));
        memset(father, 0, sizeof(to));
        memset(colorP, 0, sizeof(to));
        G = vector<vector<int>>(maxn);
        DAG = vector<set<int>>(maxn);
        scanf("%d%d", &n, &m);
        while (m--) {
            int from, to;
            scanf("%d%d", &from, &to);
            G[from].push_back(to);
            father[to] = from;
        }
        for (int i = 1; i <= n; i++) {
            if (!dfn[i])
                tarjan(i, father[i]);
        }
        calculate();
    }
}

int main()
{
    init();
    return 0;
}