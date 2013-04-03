/*
codeforce - 288B - Polo the Penguin and Houses;
graph thoery;
*/
#include<cstdio>
const int mod=(int)(1e9+7);
typedef __int64 ll;
int main() {
  int n,k;
  scanf("%d%d",&n,&k);
  ll result=1;
  for(int i=0; i<k-1; ++i) {
    result=(result*k)%mod;
  }
  for(int i=0; i<n-k; ++i) {
    result=(result*(n-k))%mod;
  }
  printf("%I64d\n",result);
}
