/*
poj3275 - Ranking the Cows;
dfs;
*/
#include<cstdio>
#include<vector>
#include<algorithm>
#define pb push_back
using namespace std;
vector<int> adj[1000];
bool visit[1000];
int n,m;
int dfs(int u) {
  visit[u]=true;
  int cnt=0;
  for(int i=0; i<adj[u].size(); ++i) {
    int v=adj[u][i];
    if(!visit[v]) {
      cnt+=1+dfs(v);
    }
  }
  return cnt;
}
int main() {
  scanf("%d%d",&n,&m);
  for(int i=0; i<m; ++i) {
    int u,v;
    scanf("%d%d",&u,&v);
    u--,v--;
    adj[u].pb(v);
  }
  int result=0;
  for(int i=0; i<n; ++i) {
    for(int j=0; j<n; ++j) {
      visit[j]=false;
    }
    result+=dfs(i);
  }
  printf("%d\n",n*(n-1)/2-result);
}
