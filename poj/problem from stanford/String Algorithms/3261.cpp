/*
poj3261 - Milk Patterns;
Suffix Array; Binary Search;
*/
#include<cstdio>
#include<algorithm>
#define pii pair<int,int>
#define mp make_pair
using namespace std;
const int N=20000;
int n,kValue,text[N],array[N],myRank[N],newRank[2][N],newArray[N],height[N],myCount[N+1];
pii order[N];
void construct(void) {
  for(int i=0; i<n; ++i) {
    order[i]=mp(text[i],i);
  }
  sort(order,order+n);
  for(int i=0; i<n; ++i) {
    array[i]=order[i].second;
    myRank[array[i]]=(i==0?1:myRank[array[i-1]]+(order[i-1].first!=order[i].first));
  }
  for(int length=1; length<n; length<<=1) {
    for(int i=0; i<n; ++i) {
      newRank[0][i]=myRank[i];
      newRank[1][i]=i+length<n?myRank[i+length]:0;
    }
    for(int i=0; i<=n; ++i) {
      myCount[i]=0;
    }
    for(int i=0; i<n; ++i) {
      myCount[newRank[1][i]]++;
    }
    for(int i=0; i<n; ++i) {
      myCount[i+1]+=myCount[i];
    }
    for(int i=n-1; i>=0; --i) {
      newArray[--myCount[newRank[1][i]]]=i;
    }
    for(int i=0; i<=n; ++i) {
      myCount[i]=0;
    }
    for(int i=0; i<n; ++i) {
      myCount[newRank[0][i]]++;
    }
    for(int i=0; i<n; ++i) {
      myCount[i+1]+=myCount[i];
    }
    for(int i=n-1; i>=0; --i) {
      array[--myCount[newRank[0][newArray[i]]]]=newArray[i];
    }
    myRank[array[0]]=1;
    for(int i=1; i<n; ++i) {
      myRank[array[i]]=myRank[array[i-1]]+(newRank[0][array[i]]!=newRank[0][array[i-1]]||newRank[1][array[i]]!=newRank[1][array[i-1]]);
    }
  }
  for(int i=0; i<n; ++i) {
    myRank[i]--;
  }
  for(int i=0,k=0; i<n; ++i) {
    if(myRank[i]>0) {
      int j=array[myRank[i]-1];
      while(i+k<n&&j+k<n&&text[i+k]==text[j+k]) {
        ++k;
      }
      height[myRank[i]]=k;
      if(k>0) {
        --k;
      }
    }
  }
}
bool check(int x) {
  int cnt=1;
  for(int i=1; i<n; ++i) {
    if(height[i]<x) {
      cnt=1;
    } else {
      cnt++;
      if(cnt>=kValue) {
        return true;
      }
    }
  }
  return false;
}
int bs(int l,int r) {
  while(r-l>1) {
    int m=(l+r)/2;
    if(check(m)) {
      l=m;
    } else {
      r=m;
    }
  }
  return check(r)?r:l;
}
int main() {
  scanf("%d%d",&n,&kValue);
  for(int i=0; i<n; ++i) {
    scanf("%d",&text[i]);
  }
  construct();
  int result=bs(0,n);
  printf("%d\n",result);
}
