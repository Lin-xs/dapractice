/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-09-25 10:07:41
 * @LastEditTime: 2022-09-25 10:27:44
 * @LastEditors: Linxs
 */
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stack>
#include <string>
#include <math.h>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <vector>

#define lowbit(x) x&(-x)

using namespace std;

struct node {
    int pos,value;
    bool operator<(node a) {
        if (value == a.value)
            return pos > a.pos;
        return value < a.value;
    }
};

const int maxn = 300000+10;
node n[maxn];
int N,c[maxn];

int query(int pos) {
    int res = 0;
    while (pos > 0) {
        res = max(c[pos], res);
        pos -= lowbit(pos);
    }
    return res;
}

void change(int pos,int len) {
    while (pos <= N) {
        c[pos] = max(c[pos], len);
        pos += lowbit(pos);
    }
}

int getmax() {
    int s = N,res=0;
    while (s > 0) {
        res = max(res, c[s]);
        s -= lowbit(s);
    }
    return res;
}

void process() {
    for (int i = 1; i <= N; i++) {
        int lis;
        lis = query(n[i].pos) + 1;
        change(n[i].pos, lis);
    }
    printf("%d\n", getmax());
}


int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int val;
        scanf("%d", &val);
        n[i].pos = i, n[i].value = val;
    }
    sort(n + 1, n+N+1);
    process();
    return 0;
}