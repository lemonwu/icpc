/*
poj2653 - Pick-up sticks;
Segment Intersect Check;
*/
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#define segment pair<Point,Point>
#define pb push_back
#define mp make_pair
using namespace std;
//point class;
const double EPSILON = 1e-9;
int signum(double x) {
  return x < -EPSILON? -1: x > EPSILON;
}
struct Point {
  double x, y;
  Point(double x = 0.0, double y = 0.0): x(x), y(y) {}
  Point &operator +=(const Point &o) {
    return x += o.x, y += o.y, *this;
  }
  Point &operator -=(const Point &o) {
    return x -= o.x, y -= o.y, *this;
  }
  Point &operator *=(double k) {
    return x *= k, y *= k, *this;
  }
  Point &operator /=(double k) {
    return x /= k, y /= k, *this;
  }
  Point rotate() const {
    return Point(-y, x);
  }
  double norm2() const;
  double norm() const;
  Point normalize() const;
  double arg() const {
    return atan2(y, x);
  }
};
Point operator ==(const Point &a, const Point &b) {
  return signum(a.x - b.x) == 0 && signum(a.y - b.y) == 0;
}
Point operator +(Point a, const Point &b) {
  return a += b;
}
Point operator -(Point a, const Point &b) {
  return a -= b;
}
Point operator *(Point a, double k) {
  return a *= k;
}
Point operator *(double k, Point a) {
  return a *= k;
}
Point operator /(Point a, double k) {
  return a /= k;
}
double det(const Point &a, const Point &b) {
  return a.x * b.y - b.x * a.y;
}
double dot(const Point &a, const Point &b) {
  return a.x * b.x + a.y * b.y;
}
double angle(const Point &a, const Point &b) {
  return atan2(det(a, b), dot(a, b));
}
double Point::norm2() const {
  return dot(*this, *this);
}
double Point::norm() const {
  return sqrt(norm2());
}
Point Point::normalize() const {
  return *this / norm();
}
//segment intersect check;
bool intersect(Point &a,Point &b,Point &c,Point &d) {
  //排斥实验
  return max(a.x,b.x)>=min(c.x,d.x)&&max(c.x,d.x)>=min(a.x,b.x)&&
         max(a.y,b.y)>=min(c.y,d.y)&&max(c.y,d.y)>=min(a.y,b.y)&&
         //跨立实验
         signum(det(c-a,b-a)*det(b-a,d-a))>=0&&
         signum(det(a-c,d-c)*det(d-c,b-c))>=0;
}
vector<segment> seg;
bool top[(int)(1e5)];
int main() {
  int n;
  while(scanf("%d",&n),n) {
    seg.clear();
    for(int i=0; i<n; ++i) {
      double x1,y1,x2,y2;
      scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
      top[i]=true;
      seg.pb(mp(Point(x1,y1),Point(x2,y2)));
    }
    for(int i=0; i<n; ++i) {
      for(int j=i+1; j<n; ++j) {
        if(intersect(seg[i].first,seg[i].second,seg[j].first,seg[j].second)) {
          top[i]=false;
          break;
        }
      }
    }
    vector<int> result;
    for(int i=0; i<n; ++i) {
      if(top[i]) {
        result.pb(i+1);
      }
    }
    printf("Top sticks:");
    for(int i=0; i<result.size(); ++i) {
      printf(" %d%s",result[i],i!=result.size()-1?",":".\n");
    }
  }
}
