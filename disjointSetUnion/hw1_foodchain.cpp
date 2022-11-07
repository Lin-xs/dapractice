/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-09-18 16:39:13
 * @LastEditTime: 2022-09-18 16:40:41
 * @LastEditors: Linxs
 */
#include<bits/stdc++.h>
using  namespace  std;
int  n,k;
int  fa[5000000+10],delta[5000000+10];
int  ans(0);
int  getf(int x){
    if(fa[x]==x)  
        return  x;
    int  tx=getf(fa[x]);
    delta[x]=(delta[x]+delta[fa[x]])%3;
    fa[x]=tx;
    return  tx;
}
void  do_one_ask(){
     int  x,y,d;
     cin>>d>>x>>y;
     d--; //attention
     if (x>n||y>n||x<1||y<1)
     {
         ans++;
         return ;
     }
     if (x==y)
     {
         if (d==0)  return ;
         if (d==1) ans++;
         return ;
     }
     int  tx=getf(x),ty=getf(y);
     if (tx==ty)
     {
         if ((delta[y]-delta[x]+3)%3!=d) //attention!!!
         {
             ans++;
             return ;
         }
         else  return ;
     }
     fa[ty]=tx;
     delta[ty]=(delta[x]-delta[y]+d+3)%3;
     
}
int  main(){
    cin>>n>>k;
    for ( int  i=1;i<=n;i++){
        fa[i]=i;
        delta[i]=0;
    }
    while (k--)
    {
        do_one_ask();
    }
    cout<<ans<< "\n" ;
}

