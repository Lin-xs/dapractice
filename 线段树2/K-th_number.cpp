/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-10-16 18:35:36
 * @LastEditTime: 2022-10-16 19:39:24
 * @LastEditors: Linxs
 */
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define maxn (int)(100000+10)
using namespace std;
int ls[maxn<<5],rs[maxn<<5],sum[maxn<<5],n,m,root[maxn],idx;
int a[maxn],sorted[maxn],len;

int getid(int a){
    return lower_bound(sorted+1,sorted+1+len,a)-sorted;
}

int init(int l,int r){
    int now=++idx;
    if(l==r)return now;
    int mid=(l+r)>>1;
    ls[now]=init(l,mid);
    rs[now]=init(mid+1,r);
    return now;
}

int insert(int num,int l,int r,int mark){
    int now=++idx;
    rs[now]=rs[mark];
    ls[now]=ls[mark];
    sum[now]=sum[mark]+1;
    if(l==r)
        return now;
    int mid=(l+r)>>1;
    if(num<=mid){
        ls[now]=insert(num,l,mid,ls[mark]);
    }
    else{
        rs[now]=insert(num,mid+1,r,rs[mark]);
    }
    return now;
}

int query(int ln,int rn,int l,int r,int kth){
    if(l==r)
        return l;
    int mid=(l+r)>>1;
    int size=sum[ls[rn]]-sum[ls[ln]];
    if(kth<=size){
        return query(ls[ln],ls[rn],l,mid,kth);
    }
    else{
        return query(rs[ln],rs[rn],mid+1,r,kth-size);
    }
    return 0;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);sorted[i]=a[i];}
    sort(sorted+1,sorted+1+n);
    len=unique(sorted+1,sorted+1+n)-sorted-1;
    root[0]=init(1,len);
    for(int i=1;i<=n;i++){
        root[i]=insert(getid(a[i]),1,len,root[i-1]);
    }
    for(int i=1;i<=m;i++){
        int l,r,k;scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",sorted[query(root[l-1],root[r],1,len,k)]);
    }
    return 0;
}