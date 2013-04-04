/*
poj1036 - Gangsters;
dynamic programming;
*/
#include<cstdio>
#include<algorithm>
using namespace std;
struct Gangster {
  int cometime,prosperity,stoutness;
  bool operator<(const Gangster &temp)const {
    return cometime<temp.cometime;
  }
} gangster[100];
int dp[100];
int main() {
  int n,stateCount,timeCount;
  scanf("%d%d%d",&n,&stateCount,&timeCount);
  for(int i=0; i<n; ++i) {
    scanf("%d",&gangster[i].cometime);
  }
  for(int i=0; i<n; ++i) {
    scanf("%d",&gangster[i].prosperity);
  }
  for(int i=0; i<n; ++i) {
    scanf("%d",&gangster[i].stoutness);
  }
  sort(gangster,gangster+n);
  int result=0;
  for(int i=0; i<n; ++i) {
    if(gangster[i].cometime>=gangster[i].stoutness) {
      dp[i]=gangster[i].prosperity;
    } else {
      dp[i]=-1;
    }
    for(int j=0; j<i; ++j) {
      if(gangster[i].cometime-gangster[j].cometime>=abs(gangster[i].stoutness-gangster[j].stoutness)&&dp[j]!=-1) {
        dp[i]=max(dp[i],dp[j]+gangster[i].prosperity);
      }
    }
    result=max(result,dp[i]);
  }
  printf("%d\n",result);
}
