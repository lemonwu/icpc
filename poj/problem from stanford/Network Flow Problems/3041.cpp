/*
poj3041 - Asteroids;
max flow; bipartite graph; König's Theorem;
*/
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int N=500*2+2;
const int M=N*(N-1);
int edgeCount,firstEdge[N],nextEdge[M],to[M],capacity[M],currentEdge[M];
int source,target,sign,flow,level[N],pre[N],queue[N];
int n,points;
void addEdge(int u,int v,int w) {
  to[edgeCount]=v;
  capacity[edgeCount]=w;
  nextEdge[edgeCount]=firstEdge[u];
  firstEdge[u]=edgeCount++;
}
bool bfs(int s,int t) {
  sign=t;
  for(int i=0; i<2*n+2; ++i) {
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
  int delta=INT_MAX,u,p;
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
          return;
        }
        sign=target;
      }
    }
    level[u]=-1;
  }
}
int main() {
  scanf("%d%d",&n,&points);
  source=2*n;
  target=2*n+1;
  for(int i=0; i<2*n+2; ++i) {
    firstEdge[i]=-1;
  }
  edgeCount=0;
  for(int i=0; i<n; ++i) {
    addEdge(source,i,1);
    addEdge(i,source,0);
  }
  for(int i=0; i<n; ++i) {
    addEdge(i+n,target,1);
    addEdge(target,i+n,0);
  }
  for(int i=0; i<points; ++i) {
    int u,v;
    scanf("%d%d",&u,&v);
    --u;
    v=v-1+n;
    addEdge(u,v,1);
    addEdge(v,u,0);
  }
  flow=0;
  while(bfs(source,target)) {
    for(int i=0; i<2*n+2; ++i) {
      currentEdge[i]=firstEdge[i];
    }
    dfs(source);
  }
  printf("%d\n",flow);
}
