/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-09-18 15:08:33
 * @LastEditTime: 2022-09-18 16:40:09
 * @LastEditors: Linxs
 */
#include <bits/stdc++.h>
using namespace std;
string str;
int a[50000+10],cnt;
int root(int x){
    if(a[x]==x) return x;
    return root(a[x]);
}
void find(int l,int r){
    int ll=root(l),rr=root(r);
    if(ll==rr){
        printf("Yes\n");
    }
    else{
        a[rr] =ll;
        cnt--;
        printf("No\n");
    }
}
int main()
{
    int m,n,l,r;
    while(scanf("%d %d",&n,&m)!=EOF){
        cnt=n;
        for(int i=1;i<=n;i++){
            a[i]=i;
        }
        for(int i=1;i<=m;i++){
            scanf("%d %d",&l,&r);
            find(l,r);
        }
        printf("%d\n",cnt);
        for(int i=1;i<=n;i++)
            if(a[i]==i) printf("%d ",i);
        printf("\n");
    }
    return 0;

}