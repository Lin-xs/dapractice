/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-10-30 21:57:46
 * @LastEditTime: 2022-10-31 00:35:00
 * @LastEditors: Linxs
 */
#include<stdio.h>
#include<string.h>
#include<stack>
#include<algorithm>
#include<vector>
#define MAX 1010
#define MAXM 1000100
#define INF 0x7ffffff
using namespace std;
int n,m,mark;//mark代表图是否连通
int head[MAX],ans;
int low[MAX],dfn[MAX];
int idx;
struct node
{
    int from,to,val,next;
    int edge_cnt;
}edge[MAXM];

void tarjan(int u,int fa)
{
    int v;
    low[u]=dfn[u]=++idx;
    int flag=1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].to;
        if(flag && v==fa){
            flag=0;
            continue;
        }
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])//如果是桥
                edge[i].edge_cnt=edge[i^1].edge_cnt=1; //标记这条边和反向边是桥
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}
void add(int u,int v,int w)
{
    edge[ans].from=u;
    edge[ans].to=v;
    edge[ans].val=w;
    edge[ans].edge_cnt=0;//没有桥
    edge[ans].next=head[u];
    head[u]=ans++;
}

int main()
{
    while(scanf("%d%d",&n,&m),n|m)
    {
        ans=0;
        memset(head,-1,sizeof(head));
        int a,b,c;
        while(m--){
            scanf("%d%d%d",&a,&b,&c);
            add(a,b,c);
            add(b,a,c);
        }

        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        idx=0;
        tarjan(1,-1);
        mark=1;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                mark=0;
                break;
            }
        }
        if(!mark)
        printf("0\n");
        else{
            int ant=INF;
            for(int i=0;i<ans;i++){
                if(edge[i].edge_cnt)
                    ant=min(ant,edge[i].val);
            }
            if(ant==INF)
                ant=-1;
            if(ant==0)
                ant=1;
            printf("%d\n",ant);
        }
    }
    return 0;
}