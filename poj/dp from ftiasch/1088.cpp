/*
poj1088 - »¬Ñ©;
dynamic programming;
*/
#include<cstdio>
#include<algorithm>
using namespace std;
int r,c,height[100][100],dp[100][100];
int dx[4]= {0,0,1,-1};
int dy[4]= {1,-1,0,0};
bool in(int x,int y) {
  return 0<=x&&x<r&&0<=y&&y<c;
}
int calculate(int x,int y) {
  if(!dp[x][y]) {
    dp[x][y]=1;
    for(int i=0; i<4; ++i) {
      int xx=x+dx[i];
      int yy=y+dy[i];
      if(in(xx,yy)&&height[xx][yy]<height[x][y]) {
        dp[x][y]=max(dp[x][y],calculate(xx,yy)+1);
      }
    }
  }
  return dp[x][y];
}
int main() {
  scanf("%d%d",&r,&c);
  for(int i=0; i<r; ++i) {
    for(int j=0; j<c; ++j) {
      scanf("%d",&height[i][j]);
    }
  }
  for(int i=0; i<r; ++i) {
    for(int j=0; j<c; ++j) {
      dp[i][j]=0;
    }
  }
  int result=1;
  for(int i=0; i<r; ++i) {
    for(int j=0; j<c; ++j) {
      result=max(result,calculate(i,j));
    }
  }
  printf("%d\n",result);
}
