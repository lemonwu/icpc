/*
poj1936 - All in All;
Greedy;
*/
#include<iostream>
#include<string>
using namespace std;
string s,t;
bool gao(void) {
  int j=0;
  for(int i=0; i<t.size(); ++i) {
    if(t[i]==s[j]) {
      j++;
    }
    if(j==s.size()) {
      return true;
    }
  }
  return false;
}
int main() {
  while(cin>>s>>t) {
    if(gao()) cout<<"Yes\n";
    else cout<<"No\n";
  }
}
