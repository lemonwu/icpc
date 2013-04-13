/*
poj1274 - The Perfect Stall;
bipartite graph; max flow;
*/
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int N=400+2;
const int M=N*(N-1);
int edgeCount,firstEdge[N],currentEdge[N],nextEdge[M],to[M],capacity[M];
int source,target,flow,sign,pre[N],level[N],queue[N];
int cows,stalls,vertexCount;
void addEdge(int u,int v,int w) {
  to[edgeCount]=v;
  capacity[edgeCount]=w;
  nextEdge[edgeCount]=firstEdge[u];
  firstEdge[u]=edgeCount++;
}
bool bfs(int s,int t) {
  sign=t;
  for(int i=0; i<vertexCount; ++i) {
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
int main() {
  while(scanf("%d%d",&cows,&stalls)!=EOF) {
    vertexCount=cows+stalls+2;
    for(int i=0; i<vertexCount; ++i) {
      firstEdge[i]=-1;
    }
    edgeCount=0;
    source=cows+stalls;
    target=cows+stalls+1;
    for(int i=0; i<cows; ++i) {
      addEdge(source,i,1);
      addEdge(i,source,0);
    }
    for(int i=0; i<stalls; ++i) {
      addEdge(i+cows,target,1);
      addEdge(target,i+cows,0);
    }
    for(int i=0; i<cows; ++i) {
      int count;
      scanf("%d",&count);
      for(int j=0; j<count; ++j) {
        int v;
        scanf("%d",&v);
        v=v-1+cows;
        addEdge(i,v,1);
        addEdge(v,i,0);
      }
    }
    flow=0;
    while(bfs(source,target)) {
      for(int i=0; i<vertexCount; ++i) {
        currentEdge[i]=firstEdge[i];
      }
      dfs(source);
    }
    printf("%d\n",flow);
  }
}
