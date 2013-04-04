/*
poj1141 - Brackets Sequence;
dynamic programming;
*/
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
string brackets;
int n,dp[100][100];
int calculate(int s,int e) {
  if(dp[s][e]==-1) {
    if(s==e) {
      dp[s][e]=1;
    } else if(s+1==e) {
      if((brackets[s]=='('&&brackets[e]==')')||(brackets[s]=='['&&brackets[e]==']')) {
        dp[s][e]=0;
      } else {
        dp[s][e]=2;
      }
    } else {
      dp[s][e]=e-s+1;
      if((brackets[s]=='('&&brackets[e]==')')||(brackets[s]=='['&&brackets[e]==']')) {
        dp[s][e]=min(dp[s][e],calculate(s+1,e-1));
      }
      for(int i=s; i<=e-1; ++i) {
        dp[s][e]=min(dp[s][e],calculate(s,i)+calculate(i+1,e));
      }
    }
  }
  return dp[s][e];
}
void output(int s,int e) {
  if(s==e) {
    if(brackets[s]=='('||brackets[s]==')') {
      cout<<"()";
    } else {
      cout<<"[]";
    }
  } else if(s+1==e) {
    if(dp[s][e]==0) {
      cout<<brackets.substr(s,2);
    } else {
      if(brackets[s]=='('||brackets[s]==')') {
        cout<<"()";
      } else {
        cout<<"[]";
      }
      if(brackets[e]=='('||brackets[e]==')') {
        cout<<"()";
      } else {
        cout<<"[]";
      }
    }
  } else {
    if(dp[s][e]==dp[s+1][e-1]&&((brackets[s]=='('&&brackets[e]==')')||(brackets[s]=='['&&brackets[e]==']'))) {
      cout<<brackets[s];
      output(s+1,e-1);
      cout<<brackets[e];
    } else {
      for(int i=s; i<=e-1; ++i) {
        if(dp[s][e]==dp[s][i]+dp[i+1][e]) {
          output(s,i);
          output(i+1,e);
          break;
        }
      }
    }
  }
}
int main() {
  getline(cin,brackets);
  n=brackets.size();
  if(n==0) {
    cout<<endl;
  } else {
    for(int i=0; i<n; ++i) {
      for(int j=i; j<n; ++j) {
        dp[i][j]=-1;
      }
    }
    calculate(0,n-1);
    output(0,n-1);
  }
}
