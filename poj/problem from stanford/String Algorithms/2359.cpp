/*
poj2359 - Questions;
Josephus; Dynamic Programming;
*/
#include<iostream>
#include<string>
using namespace std;
string str,temp;
const int N=1999;
int main() {
  while(getline(cin,temp)) {
    str+=temp;
  }
  int iter=0;
  for(int i=2; i<=str.size(); ++i) {
    iter=(iter+N)%i;
  }
  if(str[iter]=='?') {
    cout<<"Yes\n";
  } else if(str[iter]==' ') {
    cout<<"No\n";
  } else {
    cout<<"No comments\n";
  }
}
