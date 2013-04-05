/*
poj1985 - Cow Marathon;
bfs;
*/
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits>
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
using namespace std;
vector<pii> adj[40000];
int d[40000];
void bfsToIntmax(int s) {
  d[s]=INT_MAX;
  queue<int> Q;
  Q.push(s);
  while(!Q.empty()) {
    int u=Q.front();
    Q.pop();
    for(int i=0; i<adj[u].size(); ++i) {
      int v=adj[u][i].first;
      if(d[v]!=INT_MAX) {
        d[v]=INT_MAX;
        Q.push(v);
      }
    }
  }
}
int bfs(int s) {
  d[s]=0;
  queue<int> Q;
  Q.push(s);
  int t=s;
  while(!Q.empty()) {
    int u=Q.front();
    Q.pop();
    for(int i=0; i<adj[u].size(); ++i) {
      int v=adj[u][i].first;
      if(d[v]==INT_MAX) {
        d[v]=d[u]+adj[u][i].second;
        if(d[v]>d[t]) {
          t=v;
        }
        Q.push(v);
      }
    }
  }
  return t;
}
int main()
{
  int n,m;
  scanf("%d%d",&n,&m);
  for(int i=0; i<m; ++i) {
    int u,v,d;
    scanf("%d%d%d%*s",&u,&v,&d);
    --u,--v;
    adj[u].pb(mp(v,d));
    adj[v].pb(mp(u,d));
  }
  for(int i=0; i<n; ++i) {
    d[i]=INT_MAX;
  }
  int result=0;
  for(int i=0; i<n; ++i) {
    if(d[i]==INT_MAX) {
      int s=bfs(i);
      bfsToIntmax(s);
      result=max(result,d[bfs(s)]);
    }
  }
  printf("%d\n",result);
}
