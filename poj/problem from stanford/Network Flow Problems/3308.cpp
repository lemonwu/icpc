/*
poj3308 - Paratroopers;
max flow; bipartite graph; minimum cut; mimimum cost edge cover;
*/
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double oo=1e16;
const double eps=1e-16;
const int N=50*2+2;
const int M=N*(N-1);
int rows,columns,paratroopers;
double rowCost,columnCost;
int edgeCount,firstEdge[N],currentEdge[N],nextEdge[M],to[M];
double flow,capacity[M];
int source,target,sign,pre[N],level[N],queue[N];
void addEdge(int u,int v,double w) {
  to[edgeCount]=v;
  capacity[edgeCount]=w;
  nextEdge[edgeCount]=firstEdge[u];
  firstEdge[u]=edgeCount++;
}
bool bfs(int s,int t) {
  sign=t;
  for(int i=0; i<=rows+columns+1; ++i) {
    level[i]=-1;
  }
  level[t]=0;
  int head=0,tail=0;
  queue[tail++]=t;
  while(head!=tail&&level[s]==-1) {
    int u=queue[head++];
    for(int iter=firstEdge[u]; iter!=-1; iter=nextEdge[iter]) {
      if(capacity[iter^1]>eps&&level[to[iter]]==-1) {
        level[to[iter]]=level[u]+1;
        queue[tail++]=to[iter];
      }
    }
  }
  return level[s]!=-1;
}
inline void push(void) {
  double delta=oo;
  int u,p;
  for(u=target; u!=source; u=to[p^1]) {
    p=pre[u];
    delta=min(delta,capacity[p]);
  }
  for(u=target; u!=source; u=to[p^1]) {
    p=pre[u];
    capacity[p]-=delta;
    if(fabs(capacity[p])<eps) {
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
  int testCount;
  scanf("%d",&testCount);
  while(testCount>0) {
    testCount--;
    scanf("%d%d%d",&rows,&columns,&paratroopers);
    source=rows+columns;
    target=rows+columns+1;
    edgeCount=0;
    for(int i=0; i<=rows+columns+1; ++i) {
      firstEdge[i]=-1;
    }
    for(int i=0; i<rows; ++i) {
      scanf("%lf",&rowCost);
      addEdge(source,i,log(rowCost));
      addEdge(i,source,0.0);
    }
    for(int i=0; i<columns; ++i) {
      scanf("%lf",&columnCost);
      addEdge(i+rows,target,log(columnCost));
      addEdge(target,i+rows,0.0);
    }
    for(int i=0; i<paratroopers; ++i) {
      int u,v;
      scanf("%d%d",&u,&v);
      --u;
      v=rows+v-1;
      addEdge(u,v,oo);
      addEdge(v,u,0.0);
    }
    flow=0.0;
    while(bfs(source,target)) {
      for(int i=0; i<=rows+columns+1; ++i) {
        currentEdge[i]=firstEdge[i];
      }
      dfs(source);
    }
    printf("%.4lf\n",exp(flow));
  }
}
