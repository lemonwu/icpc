/*
poj1308 - Is It A Tree?;
binary search; bfs;
*/
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
using namespace std;
vector<int> map;
vector<pii> edge;
vector<vector<int> > adj(1000);
bool root[1000],visit[1000];
int bs(int l,int r,int key) {
  while(r-l>1) {
    int m=(l+r)>>1;
    if(map[m]>key) {
      r=m;
    }
    else {
      l=m;
    }
  }
  return map[l]==key?l:r;
}
bool bfs(int s,int n) {
  for(int i=0; i<n; ++i) {
    visit[i]=false;
  }
  queue<int> Q;
  visit[s]=true;
  Q.push(s);
  while(!Q.empty()) {
    int u=Q.front();
    Q.pop();
    for(int i=0; i<adj[u].size(); ++i) {
      int v=adj[u][i];
      if(visit[v]) {
        return false;
      }
      visit[v]=true;
      Q.push(v);
    }
  }
  for(int i=0; i<n; ++i) {
    if(!visit[i]) {
      return false;
    }
  }
  return true;
}
int main() {
  int caseCount=1,u,v;
  while(scanf("%d%d",&u,&v)) {
    if(u<0&&v<0) {
      break;
    }
    if(u||v) {
      map.clear();
      map.pb(u),map.pb(v);
      edge.clear();
      edge.pb(mp(u,v));
      while(scanf("%d%d",&u,&v),u||v) {
        edge.pb(mp(u,v));
        map.pb(u),map.pb(v);
      }
      sort(map.begin(),map.end());
      map.erase(unique(map.begin(),map.end()),map.end());
      for(int i=0; i<map.size(); ++i) {
        adj[i].clear();
        root[i]=true;
      }
      for(int i=0; i<edge.size(); ++i) {
        u=bs(0,map.size()-1,edge[i].first);
        v=bs(0,map.size()-1,edge[i].second);
        adj[u].pb(v),root[v]=false;
      }
      int rt=map.size();
      for(int i=0; i<map.size(); ++i) {
        if(root[i]) {
          rt=i;
          break;
        }
      }
      if(rt==map.size()) {
        printf("Case %d is not a tree.\n",caseCount++);
      }
      else {
        if(bfs(rt,map.size())) {
          printf("Case %d is a tree.\n",caseCount++);
        } else {
          printf("Case %d is not a tree.\n",caseCount++);
        }
      }
    }
    else {
      printf("Case %d is a tree.\n",caseCount++);
    }
  }
}
