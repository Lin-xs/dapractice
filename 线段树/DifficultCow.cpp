/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-10-09 17:07:05
 * @LastEditTime: 2022-10-09 20:08:14
 * @LastEditors: Linxs
 */
#include<iostream>
using namespace std;
int tree[2000100];
int cow[1000100];
int result[1001000];
int N;
 
void init(int pos,int l,int r) {
	tree[pos] = r - l + 1;
	if (l == r)
		return;
	init(pos << 1, l, (l + r)>>1);
	init((pos << 1) + 1, ((l + r)>>1) + 1, r);
	return;
}
 
int find(int num,int pos,int l,int r) {
	tree[pos]--;
	if (l == r) {
		return l;
	}
	int mid = (l + r) >> 1;
	if (num > tree[(pos << 1)]) {
		return find(num - tree[(pos << 1)], (pos << 1) + 1, mid + 1, r);
	}
	else{
		return find(num, pos << 1, l, mid);
	}
}
 
int main() {
	cin >> N;
	init(1,1,N);
	for (int i = 1;i < N;i++) {
		cin >> cow[i];
	}
	for (int i = N - 1;i > 0;i--) {
		int pos = find(cow[i] + 1, 1, 1, N);
		result[i + 1] = pos;
	}
	result[1] = find(1, 1, 1, N);
	
	for (int i = 1;i <= N;i++) {
		cout << result[i] << endl;
	}
	return 0;
}