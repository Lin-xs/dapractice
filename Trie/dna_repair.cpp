/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-10-23 23:09:52
 * @LastEditTime: 2022-10-23 23:42:46
 * @LastEditors: Linxs
 */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 5e5+10, M = 1e3+20, mod = 1e9+7, inf = 1e9;
int dp[1100][2100],sum[N],nx[N][5],cnt,head,tail,q[N],fail[N];

int ID(char x) {
    if(x == 'A') return 1;
    else if(x == 'T') return 2;
    else if(x == 'C') return 3;
    else return 0;
}
void insert(char *s) {
    int now = 1,len = strlen(s);
    for(int i = 0; i < len; ++i) {
        int index = ID(s[i]);
        if(!nx[now][index])
            nx[now][index] = ++cnt;
        now = nx[now][index];
    }
    sum[now] = 1;
}

void build() {
    head = 0, tail = 0;
    for(int i = 0; i < 4; ++i) nx[0][i] = 1;
    fail[1] = 0;
    q[tail++] = 1;
    while(head!=tail) {
        int now = q[head++];
        sum[now] |= sum[fail[now]];
        for(int i = 0; i < 4; ++i) {
            int p = fail[now];
            if(!nx[now][i]) {
                nx[now][i] = nx[p][i];
                continue;
            }
            fail[nx[now][i]] = nx[p][i];
            q[tail++] = nx[now][i];
        }
    }
}
int n;
char s[N],a[N];
int main() {
    int cas = 1;
    while(scanf("%d",&n)!=EOF) {
        if(n == 0) break;
        cnt = 1;
        memset(sum,0,sizeof(sum));
        memset(nx,0,sizeof(nx));
        memset(fail,0,sizeof(fail));
        for(int i = 1; i <= n; ++i) {
            scanf("%s",s);
            insert(s);
        }
        build();
        scanf("%s",a+1);
        n = strlen(a+1);
        for(int i = 0; i <= n; ++i)
            for(int j = 1; j <= cnt; ++j)
                dp[i][j] = inf;
        dp[0][1] = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 1; j <= cnt; ++j) {
                if(dp[i][j] == inf) continue;
                for(int k = 0; k < 4; ++k) {
                    if(k == ID(a[i+1])) {
                        if(!sum[nx[j][k]])dp[i+1][nx[j][k]] = min(dp[i+1][nx[j][k]],dp[i][j]);
                    }
                    else {
                       if(!sum[nx[j][k]]) dp[i+1][nx[j][k]] = min(dp[i+1][nx[j][k]],dp[i][j]+1);
                    }
                }
            }
        }
        int ans = inf;
        for(int i = 1; i <= cnt; ++i) {
            ans = min(dp[n][i],ans);
        }
        printf("Case %d: ",cas++);
        if(ans == inf) 
            printf("-1");
        else printf("%d",ans);
        printf("\n");
    }
    return 0;
}