/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-09-06 23:23:11
 * @LastEditTime: 2022-09-06 23:27:44
 * @LastEditors: Linxs
 */
#define N 100

int parent[N];
int getRoot(int a){
    if(parent[a] != a)
        parent[a] = getRoot(parent[a]);
    return parent[a];
}

void merge(int a, int b){
    parent[getRoot(b)] = getRoot(a);
}

bool query(int a, int b){
    return getRoot(a) == getRoot(b);
}