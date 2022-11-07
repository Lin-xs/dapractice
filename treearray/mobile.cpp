#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define maxn 1037
#define ll long long
int c[maxn][maxn];
int n;
void add(int x,int y,int k)
{
    for(int i=x;i<=n;i+=(i&-i))
        for(int j=y;j<=n;j+=(j&-j))
            c[i][j]+=k;
}
ll sum(int x,int y)
{
    ll ans=0;
    for(int i=x;i>0;i-=(i&-i))
        for(int j=y;j>0;j-=(j&-j))
            ans+=c[i][j];
    return ans;
}
int main()
{
    int mark;
    int x,y,k;
    int x1,y1,x2,y2;
    while(~scanf("%d",&mark))
    {
        if(mark==0)
            scanf("%d",&n);
        else if(mark==3)
            break;
        else if(mark==1)
        {
            scanf("%d %d %d",&x,&y,&k);
            add(x+1,y+1,k);
        }
        else
        {
            scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
            x1++,x2++,y1++,y2++;
            printf("%lld\n",sum(x2,y2)-sum(x2,y1-1)-sum(x1-1,y2)+sum(x1-1,y1-1));
        }
    }
    return 0;
}
