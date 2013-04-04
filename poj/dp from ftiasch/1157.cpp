/*
poj1157 - LITTLE SHOP OF FLOWERS;
dynamic programming;
*/
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
int flowers,vases,value[100][100],dp[100][100];
int main() {
  scanf("%d%d",&flowers,&vases);
  for(int i=0; i<flowers; ++i) {
    for(int j=0; j<vases; ++j) {
      scanf("%d",&value[i][j]);
    }
  }
  int result=0;
  for(int i=0; i<flowers; ++i) {
    for(int j=i; flowers-i<=vases-j; ++j) {
      if(i==0) {
        dp[i][j]=value[i][j];
      } else {
        dp[i][j]=-INT_MAX;
        for(int k=i-1; k<=j-1; ++k) {
          dp[i][j]=max(dp[i][j],dp[i-1][k]+value[i][j]);
        }
      }
      if(i==flowers-1) {
        result=max(result,dp[i][j]);
      }
    }
  }
  printf("%d\n",result);
}
