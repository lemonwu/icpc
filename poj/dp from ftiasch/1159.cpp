/*
poj1159 - Palindrome;
dynamic programming;
*/
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string str;
int n,dp[2][5000+1];
int main() {
  cin>>n>>str;
  int x=0,y=1;
  for(int i=0; i<=n; ++i) {
    dp[x][i]=0;
  }
  for(int i=0; i<n; ++i) {
    dp[y][0]=0;
    for(int j=0; j<n; ++j) {
      if(str[i]==str[n-1-j]) {
        dp[y][j+1]=dp[x][j]+1;
      } else {
        dp[y][j+1]=max(dp[x][j+1],dp[y][j]);
      }
    }
    swap(x,y);
  }
  int result=n-dp[x][n];
  cout<<result<<endl;
}
