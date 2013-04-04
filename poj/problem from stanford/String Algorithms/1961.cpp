/*
poj1961 - Period;
KMP;
*/
#include<iostream>
#include<string>
using namespace std;
int n,p[1000000];
string str;
void construct(void) {
  p[0]=-1;
  int j=-1;
  for(int i=1; i<n; ++i) {
    while(j!=-1&&str[j+1]!=str[i]) {
      j=p[j];
    }
    if(str[j+1]==str[i]) {
      ++j;
    }
    p[i]=j;
  }
}
int main() {
  int testCount=1;
  while(cin>>n,n) {
    cin>>str;
    cout<<"Test case #"<<testCount++<<endl;
    construct();
    for(int i=1; i<n; ++i) {
      if(p[i]!=-1) {
        int minLoop=i-p[i];
        if((i+1)%minLoop==0) {
          cout<<i+1<<" "<<(i+1)/minLoop<<endl;
        }
      }
    }
    cout<<endl;
  }
}
