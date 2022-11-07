/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-10-25 01:49:15
 * @LastEditTime: 2022-10-31 00:04:29
 * @LastEditors: Linxs
 */
//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mac = 1e5 + 10;
struct Edge
{
	int to, next;
}eg[mac << 1];
int head[mac], num = 0, dfn[mac], low[mac], stk[mac];
int top = 0, times = 0, cnt = 0;
int id[mac], vis[mac], instk[mac];//id 存储缩点后的编号
void add(int u, int v)
{
	eg[++num].to = v; eg[num].next = head[u];
	head[u] = num;
}
void tarjan(int x)
{
	dfn[x] = low[x] = ++times;
	stk[++top] = x;
	instk[x] = 1;
	for (int i = head[x]; i != -1; i = eg[i].next) {
		int v = eg[i].to;
		if (!dfn[v]){
            tarjan(v);
            low[x] = min(low[x], low[v]);
        }
		if (instk[v]) 
            low[x] = min(low[v], low[x]);
	}
	if (low[x] == dfn[x]) {
		cnt++;
		while (1) {
			int v = stk[top--];
			instk[v] = 0;
			id[v] = cnt;
			if (v == x) break;
		}
	}
}
int main()
{
	int n, m, x, y;
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) 
            tarjan(i);
	for (int i = 1; i <= n; i++) {
		for (int j = head[i]; j != -1; j = eg[j].next) {
			if (id[i] != id[eg[j].to]) 
                vis[id[i]]++;
		}
	}
	int sum = 0;
	for (int i = 1; i <= cnt; i++) {
		if (!vis[i]){
            //未被到访过
            sum++;
            x = i;
        }
	}
	if (sum == 1) {
		int ans = 0;
		for (int i = 1; i <= n; i++)
			if (id[i] == x) ans++;
		printf("%d\n", ans);
	}
	else printf("0\n");
	return 0;
}
