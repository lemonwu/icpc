/*
POJ-3281-Dining;
Max Flow;
*/
#include<cstdio>
#include<algorithm>
#include<climits>
#define in(x) (x<<1)
#define out(x) (x<<1|1)
using namespace std;
const int N=400+2;
const int M=N*(N-1);
int edgeCount,firstEdge[N],currentEdge[N],nextEdge[M],to[M],capacity[M];
int source,target,sign,flow,level[N],pre[N],queue[N];
int n,food,drink,vertexCount;
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
  scanf("%d%d%d",&n,&food,&drink);
  vertexCount=2*n+food+drink+2;
  source=2*n+food+drink;
  target=2*n+food+drink+1;
  for(int i=0; i<vertexCount; ++i) {
    firstEdge[i]=-1;
  }
  for(int i=0; i<food; ++i) {
    int v=2*n+i;
    addEdge(source,v,1);
    addEdge(v,source,0);
  }
  for(int i=0; i<drink; ++i) {
    int u=2*n+food+i;
    addEdge(u,target,1);
    addEdge(target,u,0);
  }
  for(int i=0; i<n; ++i) {
    addEdge(in(i),out(i),1);
    addEdge(out(i),in(i),0);
    int foodCount,drinkCount;
    scanf("%d%d",&foodCount,&drinkCount);
    while(foodCount) {
      foodCount--;
      int u;
      scanf("%d",&u);
      u=2*n+u-1;
      addEdge(u,in(i),1);
      addEdge(in(i),u,0);
    }
    while(drinkCount) {
      drinkCount--;
      int v;
      scanf("%d",&v);
      v=2*n+food+v-1;
      addEdge(out(i),v,1);
      addEdge(v,out(i),0);
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