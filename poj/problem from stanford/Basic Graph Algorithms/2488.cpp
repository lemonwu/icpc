/*
poj2488 - A Knight's Journey;
dfs;
*/
#include<cstdio>
#include<algorithm>
#define pii pair<int,int>
#define mp make_pair
using namespace std;
int r,c;
bool visit[26][26];
pii path[26];
const int dx[8]= {-2,-2,-1,-1,1,1,2,2};
const int dy[8]= {-1,1,-2,2,-2,2,-1,1};
bool in(int x,int y) {
  return 0<=x&&x<r&&0<=y&&y<c;
}
bool dfs(pii u,int depth) {
  if(depth+1==r*c) {
    return true;
  }
  for(int i=0; i<8; ++i) {
    int x=u.first+dy[i];
    int y=u.second+dx[i];
    if(in(x,y)&&!visit[x][y]) {
      visit[x][y]=true;
      path[depth+1]=mp(x,y);
      if(dfs(mp(x,y),depth+1)) {
        return true;
      }
      visit[x][y]=false;
    }
  }
  return false;
}
int main() {
  int caseCount;
  scanf("%d",&caseCount);
  for(int i=1; i<=caseCount; ++i) {
    scanf("%d%d",&r,&c);
    for(int j=0; j<r; ++j) {
      for(int k=0; k<c; ++k) {
        visit[j][k]=false;
      }
    }
    visit[0][0]=true;
    path[0]=mp(0,0);
    printf("Scenario #%d:\n",i);
    if(dfs(mp(0,0),0)) {
      for(int j=0; j<r*c; ++j) {
        printf("%c%d",path[j].second+'A',path[j].first+1);
      }
      puts("");
    }
    else {
      puts("impossible");
    }
    puts("");
  }
}
