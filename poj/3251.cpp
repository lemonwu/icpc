/*
POJ-3251-Big Square;
Enumerate;
*/
#include<cstdio>
#include<vector>
#include<algorithm>
#define PII pair<int,int>
#define mk make_pair
#define pb push_back
using namespace std;
int n;
char g[100][101];
int main() {
  scanf("%d",&n);
  vector<PII> p;
  for(int i=0; i<n; ++i) {
    scanf("%s",g[i]);
    for(int j=0; j<n; ++j) {
      if(g[i][j]=='J') {
        p.pb(mk(i,j));
      }
    }
  }
  int ret=0;
  int x1,x2,x3,x4,y1,y2,y3,y4;
  for(int i=0; i<p.size(); ++i) {
    x1=p[i].first;
    y1=p[i].second;
    for(int j=i+1; j<p.size(); ++j) {
      x2=p[j].first;
      y2=p[j].second;
      if((((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))>>1)<=ret) {
        continue;
      }
      if((x1+x2+y2-y1)&1) {
        continue;
      }
      if((y1+y2+x1-x2)&1) {
        continue;
      }
      x3=(x1+x2+y2-y1)>>1;
      y3=(y1+y2+x1-x2)>>1;
      x4=(x1+x2+y1-y2)>>1;
      y4=(y1+y2+x2-x1)>>1;
      if(x3<0||x3>=n||y3<0||y3>=n||x4<0||x4>=n||y4<0||y4>=n) {
        continue;
      }
      if((g[x3][y3]=='J'&&g[x4][y4]!='B')||(g[x3][y3]!='B'&&g[x4][y4]=='J')) {
        ret=max(ret,((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))>>1);
      }
    }
  }
  printf("%d\n",ret);
}