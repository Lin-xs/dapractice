/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-09-18 17:00:08
 * @LastEditTime: 2022-09-18 17:21:16
 * @LastEditors: Linxs
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn=2005;
int a[maxn];
int is[maxn];
int finds (int x){
    int par;
    if(x==a[x])
        return x;
    int temp=a[x];
    par=finds(a[x]);
    a[x]=par;
    is[x]=(is[x]+is[temp])%2;
    return par;
}
int main(){
    int n;
    scanf("%d",&n);
    int flag=0;
    for (int j=1;j<=n;j++)
    {
        flag=0;
        int m,k;
        scanf("%d%d",&m,&k);
        for (int i=1;i<=m;i++){
            a[i]=i;
            is[i]=0;
        }
        for (int i=0;i<k;i++){
            int xx,yy;
            scanf("%d%d",&xx,&yy);
            if(!flag){
                int temp1=finds(xx);
                int temp2=finds(yy);
            if(temp1==temp2&&is[xx]==is[yy]){
                flag=1;
            }
            else{
                 a[temp1]=temp2;
                 is[temp1]=(is[yy]-is[xx]+1)%2;
            }
            }
        }
        printf("Scenario #%d:\n",j);
        if(flag)
            printf("Suspicious bugs found!\n");
        else
            printf("No suspicious bugs found!\n");
        printf("\n");
 
    }
    return 0;
}