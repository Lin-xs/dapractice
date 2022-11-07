/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-10-16 21:24:52
 * @LastEditTime: 2022-10-16 22:46:36
 * @LastEditoRecs: Linxs
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;
#define maxn 20010
#define maxr 5010
int n;


struct Rectangle {
	int x1, y1, x2, y2;
	Rectangle() {}
	Rectangle(int a, int b, int c, int d): x1(a), y1(b), x2(c), y2(d) {}
} Recs[maxr];

struct Line {
	int l, r, x;
	Line() {}
	Line(int ll, int rr, int xx): l(ll), r(rr), x(xx) {}
	bool operator < (const Line& t) const { return x < t.x; }
} line1[maxr], line2[maxr];


int get_data() {
	int x = 0, f = 1; 
    char c = getchar();
	while(!isdigit(c)){ 
        if(c == '-') f = -1; 
        c = getchar(); 
    }
	while(isdigit(c)){ 
        x = x * 10 + c - '0'; 
        c = getchar(); 
    }
	return x * f;
}

int cnta, cntm, ans;

int cntv[maxn<<2], sumv[maxn<<2];
void update(int L, int R, int o, int qleft, int qright, int v) {
	int M = L + R >> 1, lc = o << 1, rc = lc | 1;
	if(qleft <= L && R <= qright) {
		cntv[o] += v;
		if(cntv[o]) 
            sumv[o] = R - L + 1;
		else if(L == R) 
            sumv[o] = 0;
		else 
            sumv[o] = sumv[lc] + sumv[rc];
		return ;
	}
	if(qleft <= M) update(L, M, lc, qleft, qright, v);
	if(qright > M) update(M+1, R, rc, qleft, qright, v);
	sumv[o] = cntv[o] ? R - L + 1 : sumv[lc] + sumv[rc];
	return ;
}

void solve() {
	sort(line1 + 1, line1 + cnta + 1);
	sort(line2 + 1, line2 + cnta + 1);
	memset(sumv, 0, sizeof(sumv));
	memset(cntv, 0, sizeof(cntv));
	int ka = 1, km = 1;
	for(int i = 1; i <= 20001; i++) {
		while(ka <= cnta && line1[ka].x == i) {
			int tmp = sumv[1];
			update(1, 20001, 1, line1[ka].l, line1[ka].r - 1, 1);
			ans += sumv[1] - tmp;
			ka++;
		}
		while(km <= cntm && line2[km].x == i) {
			int tmp = sumv[1];
			update(1, 20001, 1, line2[km].l, line2[km].r - 1, -1);
			ans += tmp - sumv[1];
			km++;
		}
	}
	return ;
}

int main() {
	n = get_data();
	for(int i = 1; i <= n; i++) {
		int x1 = get_data() + 10001, y1 = get_data() + 10001, x2 = get_data() + 10001, y2 = get_data() + 10001;
		Recs[i] = Rectangle(x1, y1, x2, y2);
		line1[++cnta] = Line(y1, y2, x1);
		line2[++cntm] = Line(y1, y2, x2);
	}
	
	solve();
	cnta = cntm = 0;
	for(int i = 1; i <= n; i++) {
		int x1 = Recs[i].x1, x2 = Recs[i].x2, y1 = Recs[i].y1, y2 = Recs[i].y2;
		line1[++cnta] = Line(x1, x2, y1);
		line2[++cntm] = Line(x1, x2, y2);
	}
	solve();
	
	printf("%d", ans);
	
	return 0;
}