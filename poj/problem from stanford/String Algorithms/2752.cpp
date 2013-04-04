/*
poj2752 - Seek the Name, Seek the Fame;
KMP; Recursion;
*/
#include<iostream>
#include<string>
using namespace std;
string str;
int p[400000];
void construct(void) {
  p[0]=-1;
  int j=-1;
  for(int i=1; i<str.size(); ++i) {
    while(j!=-1&&str[j+1]!=str[i]) {
      j=p[j];
    }
    if(str[j+1]==str[i]) {
      ++j;
    }
    p[i]=j;
  }
}
void gao(int x) {
  if(x==-1) {
    return;
  } else {
    gao(p[x]);
    cout<<x+1<<" ";
  }
}
int main() {
  while(cin>>str) {
    construct();
    gao(p[str.size()-1]);
    cout<<str.size()<<endl;
  }
}
