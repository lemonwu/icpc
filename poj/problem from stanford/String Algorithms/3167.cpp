/*
poj3167 - Cow Patterns;
KMP; Binary Indexed Trees;
*/
#include<cstdio>
#include<vector>
#define pb push_back
#define lowbit(x) ((x)&(-x))
using namespace std;
const int n=25;
int tree[n+1],s[100000],t[25000],p[25000],sSize,tSize,lessCount[25000],equalCount[25000];
vector<int> result;
void updata(int x,int add) {
  while(x<=n) {
    tree[x]+=add;
    x+=lowbit(x);
  }
}
int query(int x) {
  int sum=0;
  while(x>0) {
    sum+=tree[x];
    x-=lowbit(x);
  }
  return sum;
}
void construct(void) {
  for(int i=0; i<=n; ++i) {
    tree[i]=0;
  }
  for(int i=0; i<tSize; ++i) {
    lessCount[i]=query(t[i]-1);
    equalCount[i]=query(t[i]);
    updata(t[i],1);
  }
  for(int i=0; i<=n; ++i) {
    tree[i]=0;
  }
  p[0]=-1;
  int j=-1;
  for(int i=1; i<tSize; ++i) {
    while(j!=-1&&(lessCount[j+1]!=query(t[i]-1)||equalCount[j+1]!=query(t[i]))) {
      for(int k=i-j-1; k<i-p[j]-1; ++k) {
        updata(t[k],-1);
      }
      j=p[j];
    }
    if(lessCount[j+1]==query(t[i]-1)&&equalCount[j+1]==query(t[i])) {
      ++j;
      updata(t[i],1);
    }
    p[i]=j;
  }
}
void KMP(void) {
  for(int i=0; i<=n; ++i) {
    tree[i]=0;
  }
  int j=-1;
  for(int i=0; i<sSize; ++i) {
    while(j!=-1&&(lessCount[j+1]!=query(s[i]-1)||equalCount[j+1]!=query(s[i]))) {
      for(int k=i-j-1; k<i-p[j]-1; ++k) {
        updata(s[k],-1);
      }
      j=p[j];
    }
    if(lessCount[j+1]==query(s[i]-1)&&equalCount[j+1]==query(s[i])) {
      ++j;
      updata(s[i],1);
    }
    if(j==tSize-1) {
      result.pb(i-tSize+2);
      for(int k=i-j; k<i-p[j]; ++k) {
        updata(s[k],-1);
      }
      j=p[j];
    }
  }
}
int main() {
  scanf("%d%d%*d",&sSize,&tSize);
  for(int i=0; i<sSize; ++i) {
    scanf("%d",&s[i]);
  }
  for(int i=0; i<tSize; ++i) {
    scanf("%d",&t[i]);
  }
  construct();
  KMP();
  printf("%d\n",result.size());
  for(int i=0; i<result.size(); ++i) {
    printf("%d\n",result[i]);
  }
}
