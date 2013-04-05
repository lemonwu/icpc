/*
poj1696 - Space Ant;
Convex Hull; Gift Wrapping Algorithm;
*/
#include<cstdio>
struct Point {
  int x,y,index;
  bool out;
} p[50];
int cross(Point &p1,Point &p2,Point &p3) {
  return (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
}
int distance(Point &p1,Point &p2) {
  return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
int main() {
  int testCount;
  scanf("%d",&testCount);
  while(testCount--) {
    int n;
    scanf("%d",&n);
    int current=0;
    for(int i=0; i<n; ++i) {
      scanf("%d%d%d",&p[i].index,&p[i].x,&p[i].y);
      p[i].out=false;
      if(i>0&&(p[current].y>p[i].y||(p[current].y==p[i].y&&p[current].x>p[i].x))) {
        current=i;
      }
    }
    printf("%d %d",n,p[current].index);
    p[current].out=true;
    for(int i=0; i<n-1; ++i) {
      int next;
      for(int j=0; j<n; ++j) {
        if(!p[j].out) {
          next=j;
          break;
        }
      }
      for(int j=0; j<n; ++j) {
        if(j!=next&&!p[j].out) {
          int crossProduct=cross(p[current],p[j],p[next]);
          if(crossProduct>0) {
            next=j;
          } else if(crossProduct==0) {
            if(distance(p[current],p[j])<distance(p[current],p[next])) {
              next=j;
            }
          }
        }
      }
      printf(" %d",p[next].index);
      p[next].out=true;
      current=next;
    }
    puts("");
  }
}
