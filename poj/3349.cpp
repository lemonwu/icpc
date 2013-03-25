/*
POJ-3349-Snowflake Snow Snowflakes
Hash;
*/
#include<cstdio>
#include<vector>
#define pb push_back
using namespace std;
const int N=87719;
struct SnowFlake {
  int arm[6];
} temp;
vector<SnowFlake> snowFlake[N];
bool same(const SnowFlake &s1,const SnowFlake &s2) {
  int count1=0,count2=0;
  for(int i=0; i<6; ++i) {
    count1+=s1.arm[i];
    count2+=s2.arm[i];
  }
  if(count1!=count2) {
    return false;
  }
  vector<int> startPoint;
  for(int i=0; i<6; ++i) {
    if(s2.arm[i]==s1.arm[0]) {
      startPoint.pb(i);
    }
  }
  for(int i=0; i<startPoint.size(); ++i) {
    int x=startPoint[i];
    bool result=true;
    for(int j=0; j<6; ++j) {
      if(s1.arm[j]!=s2.arm[(x+j)%6]) {
        result=false;
        break;
      }
    }
    if(result) {
      return true;
    }
    result=true;
    for(int j=0; j<6; ++j) {
      if(s1.arm[j]!=s2.arm[(x+6-j)%6]) {
        result=false;
        break;
      }
    }
    if(result) {
      return true;
    }
  }
  return false;
}
bool check(void) {
  for(int i=0; i<N; ++i) {
    for(int j=0; j<snowFlake[i].size(); ++j) {
      for(int k=j+1; k<snowFlake[i].size(); ++k) {
        if(same(snowFlake[i][j],snowFlake[i][k])) {
          return true;
        }
      }
    }
  }
  return false;
}
int main() {
  int n;
  scanf("%d",&n);
  for(int i=0; i<n; ++i) {
    int count=0;
    for(int j=0; j<6; ++j) {
      scanf("%d",&temp.arm[j]);
      count+=temp.arm[j];
    }
    snowFlake[count%N].pb(temp);
  }
  if(check()) {
    puts("Twin snowflakes found.");
  } else {
    puts("No two snowflakes are alike.");
  }
}