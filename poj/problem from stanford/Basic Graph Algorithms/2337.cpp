/*
poj2337 - Catenyms;
euler graph;
*/
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
#define pb push_back
using namespace std;
vector<string> word;
vector<int> adj[26];
stack<int> out;
int n,degree[26],p[26];
bool exist[26],print[1000];
int find(int x) {
  return x==p[x]?x:(p[x]=find(p[x]));
}
bool checkEuler(void) {
  for(int i=0; i<26; ++i) {
    if(exist[i]) {
      p[i]=find(i);
    }
  }
  int root;
  for(int i=0; i<26; ++i) {
    if(exist[i]) {
      root=p[i];
      break;
    }
  }
  for(int i=0; i<26; ++i) {
    if(exist[i]&&root!=p[i]) {
      return false;
    }
  }
  int cnt=0;
  for(int i=0; i<26; ++i) {
    if(abs(degree[i])==1) {
      cnt++;
    }
    if(abs(degree[i])>1) {
      return false;
    }
  }
  return (cnt==2||cnt==0);
}
void constructEuler(int u) {
  for(int i=0; i<adj[u].size(); ++i) {
    int edge=adj[u][i];
    if(!print[edge]) {
      int v=word[edge][word[edge].size()-1]-'a';
      print[edge]=true;
      constructEuler(v);
      out.push(edge);
    }
  }
}
int main() {
  int caseCount;
  cin>>caseCount;
  while(caseCount--) {
    word.clear();
    for(int i=0; i<26; ++i) {
      degree[i]=0;
      p[i]=i;
      exist[i]=false;
      adj[i].clear();
    }
    cin>>n;
    for(int i=0; i<n; ++i) {
      string str;
      cin>>str;
      word.pb(str);
      int u=str[0]-'a';
      int v=str[str.size()-1]-'a';
      degree[u]--,degree[v]++;
      exist[u]=exist[v]=true;
      if(find(u)!=find(v)) {
        p[find(u)]=find(v);
      }
    }
    if(checkEuler()) {
      int sourse;
      for(int i=0; i<26; ++i) {
        if(exist[i]) {
          sourse=i;
          break;
        }
      }
      for(int i=0; i<26; ++i) {
        if(degree[i]==-1) {
          sourse=i;
          break;
        }
      }
      sort(word.begin(),word.end());
      for(int i=0; i<n; ++i) {
        int u=word[i][0]-'a';
        adj[u].pb(i);
        print[i]=false;
      }
      constructEuler(sourse);
      bool first=true;
      while(!out.empty()) {
        if(!first) {
          cout<<".";
        } else {
          first=false;
        }
        cout<<word[out.top()];
        out.pop();
      }
      cout<<endl;
    }
    else {
      cout<<"***"<<endl;
    }
  }
}
