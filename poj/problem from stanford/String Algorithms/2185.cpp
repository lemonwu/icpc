/*
poj2185 - Milking Grid;
KMP; 2D;
*/
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10000;
char grid[N][75+1];
int r,c,p[N],wide,height;
bool same(int r1,int r2) {
  for(int i=0; i<wide; ++i) {
    if(grid[r1][i]!=grid[r2][i]) {
      return false;
    }
  }
  return true;
}
void construct(int row) {
  p[0]=-1;
  int j=-1;
  if(row!=-1) {
    for(int i=1; i<c; ++i) {
      while(j!=-1&&grid[row][j+1]!=grid[row][i]) {
        j=p[j];
      }
      if(grid[row][j+1]==grid[row][i]) {
        ++j;
      }
      p[i]=j;
    }
  } else {
    for(int i=1; i<r; ++i) {
      while(j!=-1&&!same(j+1,i)) {
        j=p[j];
      }
      if(same(j+1,i)) {
        ++j;
      }
      p[i]=j;
    }
  }
}
int gcd(int a,int b) {
  return b?gcd(b,a%b):a;
}
int lcm(int a,int b) {
  return a*b/gcd(a,b);
}
int main() {
  scanf("%d%d",&r,&c);
  for(int i=0; i<r; ++i) {
    scanf("%s",grid[i]);
    construct(i);
    if(i==0) {
      wide=c-1-p[c-1];
    } else {
      wide=lcm(wide,c-1-p[c-1]);
    }
  }
  wide=min(wide,c);
  construct(-1);
  height=r-1-p[r-1];
  printf("%d\n",wide*height);
}
