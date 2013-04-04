/*
poj2408 - Anagram Groups;
Sort;
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#define pss pair<string,string>
#define mp make_pair
#define pb push_back
using namespace std;
struct Set {
  int left,right,size;
  string firstWord;
  Set() {}
  Set(int a,int b,int c,string d):left(a),right(b),size(c),firstWord(d) {}
  bool operator<(const Set &temp)const {
    if(size!=temp.size) return size>temp.size;
    else return firstWord<temp.firstWord;
  }
};
vector<pss> word;
vector<Set> set;
int main() {
  string str;
  while(cin>>str) {
    string orderedStr=str;
    sort(orderedStr.begin(),orderedStr.end());
    word.pb(mp(orderedStr,str));
  }
  sort(word.begin(),word.end());
  for(int i=0; i<word.size();) {
    int j=i+1;
    while(j<word.size()&&word[j].first==word[i].first) {
      ++j;
    }
    set.pb(Set(i,j-1,j-i,word[i].second));
    i=j;
  }
  sort(set.begin(),set.end());
  for(int i=0; i<5; ++i) {
    if(i==set.size()) {
      break;
    } else {
      cout<<"Group of size "<<set[i].size<<": ";
      for(int j=set[i].left; j<=set[i].right; ++j) {
        if(j==set[i].left||word[j].second!=word[j-1].second) {
          cout<<word[j].second<<" ";
        }
      }
      cout<<".\n";
    }
  }
}
