/*
poj1014 - Dividing;
dynamic programming;
*/
#include<cstdio>
#include<vector>
#define pb push_back
using namespace std;
int count[6],dp[20000*6+1];
vector<int> marbles;
int main() {
  int test=1;
  while(true) {
    int total=0;
    for(int i=0; i<6; ++i) {
      scanf("%d",&count[i]);
      total+=(i+1)*count[i];
    }
    if(!total) {
      break;
    }
    if(total&1) {
      printf("Collection #%d:\nCan't be divided.\n\n",test++);
    } else {
      marbles.clear();
      for(int i=0; i<6; ++i) {
        int used=0;
        if(count[i]) {
          for(int j=1; used+j<count[i]; j<<=1) {
            used+=j;
            marbles.pb((i+1)*j);
          }
          marbles.pb((i+1)*(count[i]-used));
        }
      }
      dp[0]=1;
      for(int i=1; i<=total; ++i) {
        dp[i]=0;
      }
      for(int i=0; i<marbles.size(); ++i) {
        for(int j=total; j>=0; --j) {
          if(j-marbles[i]>=0) {
            dp[j]|=dp[j-marbles[i]];
          }
        }
      }
      if(dp[total/2]) {
        printf("Collection #%d:\nCan be divided.\n\n",test++);
      } else {
        printf("Collection #%d:\nCan't be divided.\n\n",test++);
      }
    }
  }
}
