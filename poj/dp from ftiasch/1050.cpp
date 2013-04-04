/*
poj1050 - To the Max;
dynamic programming;
*/
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
int array[100+1][100+1],sum[100+1][100+1],dp[100+1];
int main() {
  int n;
  scanf("%d",&n);
  for(int i=1; i<=n; ++i) {
    for(int j=1; j<=n; ++j) {
      scanf("%d",&array[i][j]);
    }
  }
  for(int i=1; i<=n; ++i) {
    sum[i][0]=0;
    for(int j=1; j<=n; ++j) {
      sum[i][j]=sum[i][j-1]+array[i][j];
    }
  }
  int result=0;
  for(int i=1; i<=n; ++i) {
    for(int j=i; j<=n; ++j) {
      for(int k=1; k<=n; ++k) {
        dp[k]=max(sum[k][j]-sum[k][i-1],dp[k-1]+sum[k][j]-sum[k][i-1]);
        result=max(result,dp[k]);
      }
    }
  }
  printf("%d\n",result);
}
