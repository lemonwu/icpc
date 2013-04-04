/*
poj1750 - Dictionary;
Simulation;
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=11;
char prev[N],next[N];
int main() {
  scanf("%s",prev);
  int spaceCount=0;
  puts(prev);
  while(scanf("%s",next)!=EOF) {
    int sameCount=0;
    int size=min(strlen(prev),strlen(next));
    for(int i=0; i<size; ++i) {
      if(prev[i]==next[i]) {
        sameCount++;
      } else {
        break;
      }
    }
    if(sameCount<=spaceCount) {
      spaceCount=sameCount;
    } else {
      spaceCount++;
    }
    for(int i=0; i<spaceCount; ++i) {
      printf(" ");
    }
    puts(next);
    strcpy(prev,next);
  }
}
