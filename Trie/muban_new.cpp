/*
 * @Description: 
 * @Author: Linxs
 * @Date: 2022-10-23 22:09:16
 * @LastEditTime: 2022-10-23 22:09:19
 * @LastEditors: Linxs
 */
#include <iostream>
 #include <cstring>
 #include <deque>
 using namespace std;
 
 const int maxN = 1005;
 const int maxM = 1005;
 const int LETTERS = 26;
 
 struct CNode
 {
     CNode *pChilds[LETTERS];
     CNode *pPrev;
     bool bBadNode;
     CNode(){
         memset(pChilds, 0, sizeof(pChilds));
         pPrev = NULL;
         bBadNode = false;
     }
 }Tree[30000];
 
 int N, M, nNodesCount;               /* N pattern strings and M sentences */
 char patternStr[maxN];
 
 void Insert(CNode* pRoot, char *s)
 {
     for (int i = 0; s[i]; i++){
         if (!pRoot->pChilds[s[i] - 'a']) {
             pRoot->pChilds[s[i] - 'a'] = Tree + nNodesCount;
             nNodesCount++;
         }
         pRoot = pRoot->pChilds[s[i] - 'a'];
     }
     pRoot->bBadNode = true;
 }
 
 void BuildDfa()
 {
     for (int i = 0; i < LETTERS; i++)
         Tree[0].pChilds[i] = Tree + 1;
     Tree[0].pPrev = NULL;
     Tree[1].pPrev = Tree;
     deque<CNode *> q;
     q.push_back(Tree + 1);
     while (!q.empty()) {
         CNode *pRoot = q.front();
         q.pop_front();
         for (int i = 0; i < LETTERS; i++) {
             CNode *p = pRoot->pChilds[i];
             if (p) {
                 CNode *pPrev = pRoot->pPrev;
                 while (!pPrev->pChilds[i])
                     pPrev = pPrev->pPrev;
                 p->pPrev = pPrev->pChilds[i];
                 if (p->pPrev->bBadNode)
                     p->bBadNode = true;
                 q.push_back(p);
             }
         }
     }
 }
 
 bool SearchDfa(char *s)
 {
     CNode *p = Tree + 1;
     for (int i = 0; s[i]; i++) {
         while (!p->pChilds[s[i] - 'a'])
             p = p->pPrev;
         p = p->pChilds[s[i] - 'a'];
         if (p->bBadNode) return true;
     }
     return false;
 }
 
 int main()
 {
     char s[maxN];
     nNodesCount = 2;
 
     cin >> N;
     for (int i = 0; i < N; i++) {
         cin >> patternStr;
         Insert(Tree + 1, patternStr);
     }
 
     BuildDfa();
 
     cin >> M;
     for (int i = 0; i < M; i++){
         cin >> s;
         if (SearchDfa(s)) printf("YES\n");
         else printf("NO\n");
     }
 
     //system("pause");
     return 0;
 }