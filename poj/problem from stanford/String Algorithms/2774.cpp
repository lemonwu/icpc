/*
poj2774 - Long Long Message;
Suffix Array;
*/
#include<iostream>
#include<climits>
#include<string>
#include<algorithm>
#define pii pair<int,int>
#define mp make_pair
using namespace std;
typedef long long ll;
const int N=200001;
int n,text[N],array[N],myRank[N],newRank[2][N],newArray[N],height[N],myCount[N+1];
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
int main() {
  string s,t;
  cin>>s>>t;
  for(int i=0; i<s.size(); ++i) {
    text[i]=s[i];
  }
  text[s.size()]=INT_MAX;
  for(int i=0; i<t.size(); ++i) {
    text[i+1+s.size()]=t[i];
  }
  n=s.size()+1+t.size();
  construct();
  int result=0;
  for(int i=1; i<n; ++i) {
    if(max(array[i-1],array[i])>s.size()&&min(array[i-1],array[i])<s.size()) {
      result=max(result,height[i]);
    }
  }
  cout<<result<<endl;
}
