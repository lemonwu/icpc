/*
poj1273 - Drainage Ditches;
max flow;
*/
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int N=200;
const int M=N*(N-1);
int edgeCount,firstEdge[N],currentEdge[N],nextEdge[M],to[M],capacity[M];
int source,target,flow,sign,pre[N],level[N],queue[N];
int n,m;
void addEdge(int u,int v,int w) {
  to[edgeCount]=v;
  capacity[edgeCount]=w;
  nextEdge[edgeCount]=firstEdge[u];
  firstEdge[u]=edgeCount++;
}
bool bfs(int s,int t) {
  sign=t;
  for(int i=0; i<n; ++i) {
    level[i]=-1;
  }
  level[t]=0;
  int head=0,tail=0;
  queue[tail++]=t;
  while(head!=tail&&level[s]==-1) {
    int u=queue[head++];
    for(int iter=firstEdge[u]; iter!=-1; iter=nextEdge[iter]) {
      if(capacity[iter^1]>0&&level[to[iter]]==-1) {
        level[to[iter]]=level[u]+1;
        queue[tail++]=to[iter];
      }
    }
  }
  return level[s]!=-1;
}
inline void push(void) {
  int delta=INT_MAX;
  int u,p;
  for(u=target; u!=source; u=to[p^1]) {
    p=pre[u];
    delta=min(delta,capacity[p]);
  }
  for(u=target; u!=source; u=to[p^1]) {
    p=pre[u];
    capacity[p]-=delta;
    if(!capacity[p]) {
      sign=to[p^1];
    }
    capacity[p^1]+=delta;
  }
  flow+=delta;
}
void dfs(int u) {
  if(u==target) {
    push();
  } else {
    for(int &iter=currentEdge[u]; iter!=-1; iter=nextEdge[iter]) {
      if(capacity[iter]>0&&level[to[iter]]+1==level[u]) {
        pre[to[iter]]=iter;
        dfs(to[iter]);
        if(level[sign]>level[u]) {
          return ;
        }
        sign=target;
      }
    }
    level[u]=-1;
  }
}
int main() {
  while(scanf("%d%d",&m,&n)!=EOF) {
    for(int i=0; i<n; ++i) {
      firstEdge[i]=-1;
    }
    edgeCount=0;
    for(int i=0; i<m; ++i) {
      int u,v,w;
      scanf("%d%d%d",&u,&v,&w);
      --u,--v;
      addEdge(u,v,w);
      addEdge(v,u,0);
    }
    source=0;
    target=n-1;
    flow=0;
    while(bfs(source,target)) {
      for(int i=0; i<n; ++i) {
        currentEdge[i]=firstEdge[i];
      }
      dfs(source);
    }
    printf("%d\n",flow);
  }
}
