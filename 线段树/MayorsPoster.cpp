/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-10-09 20:28:35
 * @LastEditTime: 2022-10-09 21:28:48
 * @LastEditors: Linxs
 */
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

#define N 210000  // 由于数据太多

struct node
{
    int l, r;
}val[N];

struct point
{
    int l, r, flag;
}tree[N*4];

int x[N*2], h[N*1000];  // h数组为什么存这么多，因为1 <= i <= n, 1 <= l i <= ri <= 10000000.

void Build(int root, int l, int r)  // 建树
{
    tree[root].l = l;
    tree[root].r = r;

    tree[root].flag = false;

    if(l == r)
        return ;

    Build(root*2, l, (l+r)/2);
    Build(root*2+1, (l+r)/2+1, r);

}

void update(int root)  // 更新
{
    if(tree[root*2].flag && tree[root*2+1].flag)
        tree[root].flag = 1;
}

int query(int root, int l, int r)  // 看是否可以看到，如果可以看到return 1；else return0；
{
    if(tree[root].flag)  // 如果被遮住，return0；
        return 0; 

    if(tree[root].l == tree[root].r)  // 如果本节点没有被遮住，而且到了叶节点，就返回1，本节点flag置为1，即已被遮住
    { 
        tree[root].flag = 1;
        return 1;
    }

    update(root);  // 更新root节点

    int mid = (tree[root].l+tree[root].r)/2;

    if(r <= mid)
        return query(2*root, l, r);
    else if(l > mid)
        return query(2*root+1, l, r);
    else
        return query(2*root, l, mid)+query(2*root+1, mid+1, r);

}
int main()
{
    int c, n;

    scanf("%d", &c);

    while(c--)
    {
        scanf("%d", &n);
        int k = 0;

        for(int i = 1; i <= n; i++)
        {
            scanf("%d%d", &val[i].l, &val[i].r);
            x[k++] = val[i].l, x[k++] = val[i].r;  // x数组存各个海报的位置
        }

        sort(x, x+k);
        k = unique(x, x+k)-x;  // 去重，排序

        Build(1, 0, k-1); // 建树，总共有k-1个点，就有k-1个节点

        for(int i = 0; i < k; i++)
            h[x[i]] = i;  // 把各个节点的值离散化，就是把中间的有的没得全没了，只留海报左右两个端点的值存到h数组，作为节点的l，r值
 
        int ans = 0;
        for(int i = n; i > 0; i--)
            if(query(1, h[val[i].l], h[val[i].r]))  // 查询
                ans++;
                
        printf("%d", ans);
    }
    return 0;
}