/*
poj1191 - ∆Â≈Ã∑÷∏Ó;
dynamic programming;
*/
#include<cstdio>
#include<cmath>
#include<climits>
#include<algorithm>
using namespace std;
int array[8][8],sum[8+1][8+1],dp[14][8][8][8][8];
int rectangle(int i,int j,int p,int q) {
  int result=sum[p+1][q+1]-sum[i][q+1]-sum[p+1][j]+sum[i][j];
  return result*result;
}
int calculate(int i,int j,int k,int p,int q) {
  if(dp[i][j][k][p][q]==-1) {
    if(i==0) {
      dp[i][j][k][p][q]=rectangle(j,k,p,q);
    } else {
      dp[i][j][k][p][q]=INT_MAX;
      if(i+1<=(p-j+1)*(q-k+1)) {
        for(int x=j; x<p; ++x) {
          if(calculate(i-1,j,k,x,q)!=-2) {
            dp[i][j][k][p][q]=min(dp[i][j][k][p][q],calculate(i-1,j,k,x,q)+rectangle(x+1,k,p,q));
          }
          if(calculate(i-1,x+1,k,p,q)!=-2) {
            dp[i][j][k][p][q]=min(dp[i][j][k][p][q],rectangle(j,k,x,q)+calculate(i-1,x+1,k,p,q));
          }
        }
        for(int x=k; x<q; ++x) {
          if(calculate(i-1,j,k,p,x)!=-2) {
            dp[i][j][k][p][q]=min(dp[i][j][k][p][q],calculate(i-1,j,k,p,x)+rectangle(j,x+1,p,q));
          }
          if(calculate(i-1,j,x+1,p,q)!=-2) {
            dp[i][j][k][p][q]=min(dp[i][j][k][p][q],rectangle(j,k,p,x)+calculate(i-1,j,x+1,p,q));
          }
        }
        if(dp[i][j][k][p][q]==INT_MAX) {
          dp[i][j][k][p][q]=-2;
        }
      } else {
        dp[i][j][k][p][q]=-2;
      }
    }
  }
  return dp[i][j][k][p][q];
}
int main() {
  int n;
  scanf("%d",&n);
  for(int i=0; i<8; ++i) {
    for(int j=0; j<8; ++j) {
      scanf("%d",&array[i][j]);
    }
  }
  for(int i=0; i<9; ++i) {
    for(int j=0; j<9; ++j) {
      if(i==0||j==0) {
        sum[i][j]=0;
      } else {
        sum[i][j]=array[i-1][j-1]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
      }
    }
  }
  for(int i=0; i<n; ++i) {
    for(int j=0; j<8; ++j) {
      for(int k=0; k<8; ++k) {
        for(int p=j; p<8; ++p) {
          for(int q=k; q<8; ++q) {
            dp[i][j][k][p][q]=-1;
          }
        }
      }
    }
  }
  double sigema=sqrt(((double)calculate(n-1,0,0,7,7))/n-pow(((double)sum[8][8])/n,2.0));
  printf("%.3lf\n",sigema);
}
