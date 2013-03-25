/*
POJ-3498-March of the Penguins;
Max Flow; Dinic;
*/
#include<cstdio>
#include<climits>
#include<vector>
#include<algorithm>
#define pdd pair<double,double>
#define mp make_pair
#define pb push_back
#define in(x) (x<<1)
#define out(x) (x<<1|1)
using namespace std;
const int N=201;
const int M=N*(N-1);
const double eps=1e-10;
int edgeCount,firstEdge[N],nextEdge[M],to[M],capacity[M],currentEdge[M];
int source,target,sign,flow,level[N],pre[N],queue[N];
int n,m,penguins[100],capacityRecord[M];
double limitDistant;
vector<pdd> coordinate;
vector<int> result;
bool ok(pdd a,pdd b) {
  return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second)+eps<=limitDistant*limitDistant;
}
void addEdge(int u,int v,int w) {
  to[edgeCount]=v;
  capacityRecord[edgeCount]=w;
  nextEdge[edgeCount]=firstEdge[u];
  firstEdge[u]=edgeCount++;
}
bool bfs(int s,int t) {
  sign=t;
  for(int i=0; i<=2*n; ++i) {
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
  int testCount;
  scanf("%d",&testCount);
  while(testCount) {
    testCount--;
    scanf("%d%lf",&n,&limitDistant);
    source=2*n;
    for(int i=0; i<=2*n; ++i) {
      firstEdge[i]=-1;
    }
    edgeCount=0;
    coordinate.clear();
    for(int i=0; i<n; ++i) {
      double x,y;
      int ni,mi;
      scanf("%lf%lf%d%d",&x,&y,&ni,&mi);
      coordinate.pb(mp(x,y));
      penguins[i]=ni;
      int u=in(i);
      int v=out(i);
      addEdge(u,v,mi);
      addEdge(v,u,0);
    }
    for(int i=0; i<n; ++i)
      for(int j=i+1; j<n; ++j)
        if(ok(coordinate[i],coordinate[j])) {
          int u,v;
          u=out(i);
          v=in(j);
          addEdge(u,v,INT_MAX);
          addEdge(v,u,0);
          u=out(j);
          v=in(i);
          addEdge(u,v,INT_MAX);
          addEdge(v,u,0);
        }
    int penguinsCount=0;
    for(int i=0; i<n; ++i) {
      penguinsCount+=penguins[i];
      int v=in(i);
      addEdge(source,v,penguins[i]);
      addEdge(v,source,0);
    }
    result.clear();
    for(int i=0; i<n; ++i) {
      target=in(i);
      for(int j=0; j<edgeCount; ++j) {
        capacity[j]=capacityRecord[j];
      }
      flow=0;
      while(bfs(source,target)) {
        for(int j=0; j<=2*n; ++j) {
          currentEdge[j]=firstEdge[j];
        }
        dfs(source);
      }
      if(flow==penguinsCount) {
        result.pb(i);
      }
    }
    if(result.empty()) {
      puts("-1");
    } else {
      for(int i=0; i<result.size(); ++i) {
        printf("%d%s",result[i],i==result.size()-1?"\n":" ");
      }
    }
  }
}