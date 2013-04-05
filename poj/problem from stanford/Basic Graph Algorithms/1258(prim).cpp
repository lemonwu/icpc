/*
poj1258 - Agri-Net;
minimum spanning tree; prim; kruskal;
*/
#include<cstdio>
#include<queue>
#include<algorithm>
#include<climits>
#define pii pair<int,int>
#define mp make_pair
using namespace std;
int n,dist[100][100],d[100];
priority_queue<pii,vector<pii>,greater<pii> > Q;
bool visit[100];
int prim() {
  for(int i=0; i<n; ++i) {
    d[i]=INT_MAX;
    visit[i]=false;
  }
  d[0]=0;
  while(!Q.empty()) {
    Q.pop();
  }
  Q.push(mp(0,0));
  int sum=0;
  while(!Q.empty()) {
    pii current=Q.top();
    Q.pop();
    int u=current.second;
    if(!visit[u]) {
      visit[u]=true;
      sum+=current.first;
      for(int i=0; i<n; ++i) {
        if(!visit[i]&&dist[u][i]<d[i]) {
          d[i]=dist[u][i];
          Q.push(mp(d[i],i));
        }
      }
    }
  }
  return sum;
}
int main() {
  while(scanf("%d",&n)!=EOF) {
    for(int i=0; i<n; ++i) {
      for(int j=0; j<n; ++j) {
        scanf("%d",&dist[i][j]);
      }
    }
    printf("%d\n",prim());
  }
}
