/*
poj1228 - Grandpa's Estate;
Stable Convex Hull; Gift Wrapping Algorithm;
*/
#include<cstdio>
#include<vector>
#define pb push_back
using namespace std;
struct Point {
  int x,y;
  bool used;
} p[1000];
int cross(Point &p1,Point &p2,Point &p3) {
  return (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
}
int getDistance(Point &p1,Point &p2) {
  return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
vector<int> to;
bool isStable(int n,int current) {
  while(true) {
    int next;
    to.clear();
    for(int i=0; i<n; ++i) {
      if(!p[i].used) {
        next=i;
        to.pb(next);
        break;
      }
    }
    if(to.empty()) {
      return true;
    }
    for(int i=0; i<n; ++i) {
      if(i!=next&&i!=current&&!p[i].used) {
        int crossProduct=cross(p[current],p[i],p[next]);
        if(crossProduct>0) {
          next=i;
          to.clear();
          to.pb(next);
        } else if(crossProduct==0) {
          if(getDistance(p[current],p[i])>getDistance(p[current],p[next])) {
            next=i;
          }
          to.pb(i);
        }
      }
    }
    if(to.size()==1) {
      return false;
    } else {
      for(int i=0; i<to.size(); ++i) {
        p[to[i]].used=true;
      }
      current=next;
    }
  }
  return false;
}
int main() {
  int testCount;
  scanf("%d",&testCount);
  while(testCount--) {
    int n;
    scanf("%d",&n);
    int current=0;
    for(int i=0; i<n; ++i) {
      scanf("%d%d",&p[i].x,&p[i].y);
      p[i].used=false;
      if(i>0&&(p[current].y>p[i].y||(p[current].y==p[i].y&&p[current].x>p[i].x))) {
        current=i;
      }
    }
    if(n>=6&&isStable(n,current)) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
}
