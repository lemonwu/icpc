/*
poj2318 - TOYS;
Binary Search;
*/
#include<cstdio>
struct Point {
  int x,y;
};
struct Segment {
  Point p1,p2;
} segment[5001];
int count[5001],n,m,x1,y1,x2,y2;
int cross(Point &p1,Point &p2,Point &p3) {
  return (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
}
bool onLeft(Point &p,Segment &s) {
  return cross(p,s.p2,s.p1)>0;
}
int bs(int l,int r,Point &p) {
  while(r-l>1) {
    int m=(l+r)>>1;
    if(onLeft(p,segment[m])) {
      r=m;
    } else {
      l=m;
    }
  }
  return onLeft(p,segment[l])?l:r;
}
int main() {
  bool firstTest=true;
  while(scanf("%d%d%d%d%d%d",&n,&m,&x1,&y1,&x2,&y2),n) {
    if(firstTest) {
      firstTest=false;
    } else {
      puts("");
    }
    for(int i=0; i<n; ++i) {
      segment[i].p1.y=y1;
      segment[i].p2.y=y2;
      scanf("%d%d",&segment[i].p1.x,&segment[i].p2.x);
    }
    segment[n].p1.x=x2;
    segment[n].p1.y=y1;
    segment[n].p2.x=x2;
    segment[n].p2.y=y2;
    ++n;
    for(int i=0; i<=n; ++i) {
      count[i]=0;
    }
    for(int i=0; i<m; ++i) {
      Point temp;
      scanf("%d%d",&temp.x,&temp.y);
      count[bs(0,n-1,temp)]++;
    }
    for(int i=0; i<n; ++i) {
      printf("%d: %d\n",i,count[i]);
    }
  }
}
