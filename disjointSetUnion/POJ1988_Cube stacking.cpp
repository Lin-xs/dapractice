/*
 * @Description: POJ 1988 Cube stacking
 * @Author: Linxs
 * @Date: 2022-09-06 23:51:43
 * @LastEditTime: 2022-09-07 09:58:47
 * @LastEditors: Linxs
 */

#include<iostream>
using namespace std;
const int N = 30000;

int parent[N+10], total[N+10], under[N+10];

int getRoot(int a){
    if(parent[a] != a){
        parent[a] = getRoot(parent[a]);
        under[a] += total[parent[a]];
    }
    return parent[a];
}

int merge(int a, int b){
    // 将a放到b上
    parent[getRoot(b)] = getRoot(a);
    total[parent[a]] += total[parent[b]];
}
