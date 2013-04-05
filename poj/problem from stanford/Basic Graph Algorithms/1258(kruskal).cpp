/*
poj1258 - Agri-Net;
minimum spanning tree; prim; kruskal;
*/
#include<cstdio>
#include<vector>
#include<algorithm>
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
int p[100];
int find(int x) {
  return x==p[x]?x:(p[x]=find(p[x]));
}
int main() {
  int n;
  while(scanf("%d",&n)!=EOF) {
    edge.clear();
    for(int i=0; i<n; ++i) {
      for(int j=0; j<n; ++j) {
        int weight;
        scanf("%d",&weight);
        if(i!=j) {
          edge.pb(Edge(i,j,weight));
        }
      }
    }
    sort(edge.begin(),edge.end());
    for(int i=0; i<n; ++i) {
      p[i]=i;
    }
    int sum=0;
    for(int i=0; i<edge.size(); ++i) {
      int u=find(edge[i].u);
      int v=find(edge[i].v);
      if(u!=v) {
        p[u]=v;
        sum+=edge[i].weight;
      }
    }
    printf("%d\n",sum);
  }
}
