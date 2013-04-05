/*
poj1164 - The Castle;
dfs;
*/
#include<cstdio>
#include<algorithm>
#define west 1
#define north 2
#define east 4
#define south 8
using namespace std;
int r,c,graph[50][50];
bool visit[50][50];
bool in(int x,int y) {
  return 0<=x&&x<r&&0<=y&&y<c;
}
int dfs(int x,int y) {
  int area=1;
  visit[x][y]=true;
  if(!(graph[x][y]&west)&&in(x,y-1)&&!visit[x][y-1]) {
    area+=dfs(x,y-1);
  }
  if(!(graph[x][y]&north)&&in(x-1,y)&&!visit[x-1][y]) {
    area+=dfs(x-1,y);
  }
  if(!(graph[x][y]&east)&&in(x,y+1)&&!visit[x][y+1]) {
    area+=dfs(x,y+1);
  }
  if(!(graph[x][y]&south)&&in(x+1,y)&&!visit[x+1][y]) {
    area+=dfs(x+1,y);
  }
  return area;
}
int main() {
  scanf("%d%d",&r,&c);
  for(int i=0; i<r; ++i) {
    for(int j=0; j<c; ++j) {
      scanf("%d",&graph[i][j]);
      visit[i][j]=false;
    }
  }
  int count=0;
  int maxArea=0;
  for(int i=0; i<r; ++i) {
    for(int j=0; j<c; ++j) {
      if(!visit[i][j]) {
        count++;
        maxArea=max(maxArea,dfs(i,j));
      }
    }
  }
  printf("%d\n%d\n",count,maxArea);
}
