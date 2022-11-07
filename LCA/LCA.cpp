/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-11-06 21:30:53
 * @LastEditTime: 2022-11-06 23:47:14
 * @LastEditors: Linxs
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int num_node = 40010;
struct edge{
    int to, next, weight;
}e[num_node<<1];
int head[num_node], total;
int ancestor[num_node][20], max_edge[num_node][20], depth[num_node], lg[num_node], fa[num_node];
void add(int x, int y, int w){
    e[++total].to = y;
    e[total].next = head[x];
    e[total].weight = w;
    head[x] = total;
}

void dfs(int now, int father, int weight){
    //now 代表当前节点,father代表父节点,weight代表当前到父亲的边权.
    ancestor[now][0] = father;
    max_edge[now][0] = weight;
    fa[now] = father;
    depth[now] = depth[father] + 1;
    for(int i = 1; i <= lg[depth[now]]; i++){
        ancestor[now][i] = ancestor[ancestor[now][i-1]][i-1];
        max_edge[now][i] = max(max_edge[now][i-1], max_edge[ancestor[now][i-1]][i-1]);
    }

    for(int i = head[now]; i; i = e[i].next){
        if(e[i].to != father)
            dfs(e[i].to, now, e[i].weight);
    }

}

int lca(int a, int b){
    if(depth[a] < depth[b])
        swap(a, b);
    while(depth[a] > depth[b]){
        a = ancestor[a][lg[depth[a]-depth[b]]-1];
    }
    if(a == b) return a;
    for(int k = lg[depth[a]]-1; k >= 0; k--)
        if(ancestor[a][k] != ancestor[b][k])
            a = ancestor[a][k], b = ancestor[b][k];
    return ancestor[a][0];
}

int max_edge_in_path(int a, int b){
    //b是a的祖先, depth[b] <= depth[a]
    if(depth[a] < depth[b])
        swap(a, b);
    
    int res = 0;
    while(depth[a] > depth[b]){
        res = max(res, max_edge[a][lg[depth[a]-depth[b]]-1]);
        a = ancestor[a][lg[depth[a]-depth[b]]-1];
    }
    return res;
}

int main(void){
    for(int i = 1; i < num_node; ++i)
		lg[i] = lg[i-1] + (1 << lg[i-1] == i);
    int n, s, e, w, q, a, b, l, ans;
    scanf("%d", &n);
    for(int i = 0; i < n-1; i++){
        scanf("%d %d %d", &s, &e, &w);
        add(s, e, w);
        add(e, s, w);
    }
    dfs(1, 0, 0);
    scanf("%d", &q);
    for(int i = 0; i < q; i++){
        scanf("%d %d", &a, &b);
        l = lca(a, b);
        // printf("lca of %d and %d:%d maxedge=", a, b, l);
        ans = max(max_edge_in_path(a, l), max_edge_in_path(b, l));
        printf("%d\n", ans);
    }
    
    return 0;
}