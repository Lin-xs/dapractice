/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-09-25 17:55:33
 * @LastEditTime: 2022-09-25 18:56:37
 * @LastEditors: Linxs
 */
#include<iostream>
#include<cstdio>
using namespace std;

int n,m,c[100010],d[100010],cnt,v[100010];
int head[100010],tot,tree[100010];

struct strabc{
	int to,next;
}s[100010];

void add(int x,int y){
	s[++tot].to=y;
	s[tot].next=head[x];
	head[x]=tot;
}

void dfs(int x){
	c[x]=++cnt;
	for(int i=head[x];i;i=s[i].next)
		dfs(s[i].to);
	d[x]=cnt; 
}

void find(int x,int y){
	for(;x<=n;x+=x&(-x))
		tree[x]+=y;
}

int ans(int x){
	int sum=0;
	for(;x;x-=x&(-x))
		sum+=tree[x];
	return sum;
}

int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1);
	for(int i=1;i<=n;i++){
		find(c[i],1);
		v[i]=1;
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		char k;
		int t;
		cin>>k;
		scanf("%d",&t);
		if(k=='C'){
			if(v[t]) find(c[t],-1);
			else find(c[t],1);
			v[t]=1-v[t];
		}
		else
			 cout<<ans(d[t])-ans(c[t]-1)<<endl;
	}
}

