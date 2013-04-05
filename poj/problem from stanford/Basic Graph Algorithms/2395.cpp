/*
poj2395 - Out of Hay;
minimum spanning tree; kruskal;
*/
#include<cstdio>
#include<algorithm>
#include<vector>
#define pb push_back
using namespace std;
struct Edge {
  int u,v,weight;
  Edge() {}
  Edge(int a,int b,int c):u(a),v(b),weight(c) {}
  bool operator<(const Edge &tmp)const {
    return weight<tmp.weight;
  }
};
vector<Edge> edge;
int n,m,p[2000];
int find(int x) {
  return x==p[x]?x:(p[x]=find(p[x]));
}
int main() {
  scanf("%d%d",&n,&m);
  for(int i=0; i<m; ++i) {
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    u--,v--;
    edge.pb(Edge(u,v,w));
  }
  sort(edge.begin(),edge.end());
  for(int i=0; i<n; ++i) {
    p[i]=i;
  }
  int max_edge=0;
  for(int i=0; i<m; ++i) {
    int u=find(edge[i].u);
    int v=find(edge[i].v);
    if(u!=v) {
      max_edge=max(max_edge,edge[i].weight);
      p[u]=v;
    }
  }
  printf("%d\n",max_edge);
}
