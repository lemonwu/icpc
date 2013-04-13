/*
poj2112 - Optimal Milking;
max flow; bianry search; floyd-warshall algorithm;
*/
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int N=232;
const int M=N*(N-1);
int edgeCount,firstEdge[N],currentEdge[N],nextEdge[M],to[M],capacity[M];
int source,target,flow,sign,pre[N],level[N],queue[N];
int cows,machines,cowLimits,dist[N][N];
void floydWarshall() {
  for(int k=0; k<cows+machines; ++k) {
    for(int i=0; i<cows+machines; ++i) {
      for(int j=0; j<cows+machines; ++j) {
        if(dist[i][k]!=INT_MAX&&dist[k][j]!=INT_MAX) {
          dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
        }
      }
    }
  }
}
void addEdge(int u,int v,int w) {
  to[edgeCount]=v;
  capacity[edgeCount]=w;
  nextEdge[edgeCount]=firstEdge[u];
  firstEdge[u]=edgeCount++;
}
bool bfs(int s,int t) {
  sign=t;
  for(int i=0; i<cows+machines+2; ++i) {
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
          return;
        }
        sign=target;
      }
    }
    level[u]=-1;
  }
}
bool check(int distLimits) {
  for(int i=0; i<cows+machines+2; ++i) {
    firstEdge[i]=-1;
  }
  edgeCount=0;
  for(int i=machines; i<machines+cows; ++i) {
    addEdge(source,i,1);
    addEdge(i,source,0);
  }
  for(int i=0; i<machines; ++i) {
    addEdge(i,target,cowLimits);
    addEdge(target,i,0);
  }
  for(int i=machines; i<machines+cows; ++i) {
    for(int j=0; j<machines; ++j) {
      if(dist[i][j]<=distLimits) {
        addEdge(i,j,1);
        addEdge(j,i,0);
      }
    }
  }
  flow=0;
  while(bfs(source,target)) {
    for(int i=0; i<cows+machines+2; ++i) {
      currentEdge[i]=firstEdge[i];
    }
    dfs(source);
  }
  return flow==cows;
}
int bs(int l,int r) {
  while(r-l>1) {
    int m=(l+r)>>1;
    if(check(m)) {
      r=m;
    } else {
      l=m;
    }
  }
  return check(l)?l:r;
}
int main() {
  scanf("%d%d%d",&machines,&cows,&cowLimits);
  source=cows+machines;
  target=cows+machines+1;
  for(int i=0; i<cows+machines; ++i) {
    for(int j=0; j<cows+machines; ++j) {
      scanf("%d",&dist[i][j]);
      if(!dist[i][j]) {
        dist[i][j]=INT_MAX;
      }
    }
  }
  floydWarshall();
  printf("%d\n",bs(0,200*230));
}
