/*
poj1147 - Binary codes;
Sort; Recursion;
*/
#include<cstdio>
#include<algorithm>
#define pii pair<int,int>
#define mp make_pair
using namespace std;
int n,lastColumn[3000],firstRow[3000],currentColumn[2][3000],rank[3000];
pii sorted[3000];
int main() {
  scanf("%d",&n);
  int zeroCount=0;
  for(int i=0; i<n; ++i) {
    scanf("%d",&lastColumn[i]);
    if(!lastColumn[i]) {
      zeroCount++;
    }
    sorted[i]=mp(lastColumn[i],i);
  }
  stable_sort(sorted,sorted+n);
  for(int i=0; i<n; ++i) {
    rank[sorted[i].second]=i;
  }
  int x=0,y=1;
  for(int i=0; i<n; ++i) {
    if(i<zeroCount) {
      currentColumn[x][i]=0;
    } else {
      currentColumn[x][i]=1;
    }
  }
  for(int i=0; i<n; ++i) {
    firstRow[i]=currentColumn[x][0];
    for(int j=0; j<n; ++j) {
      currentColumn[y][rank[j]]=currentColumn[x][j];
    }
    swap(x,y);
  }
  for(int i=0; i<n; ++i) {
    printf("%d%s",firstRow[i],(i==n-1)?"\n":" ");
  }
}
