/*
poj3525 - Most Distant Point from the Sea;
Binary Search; Half-plane Intersection; Convex Hull;
*/
#include<cstdio>
#include<cmath>
#include<algorithm>
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
  void print() {
    printf("<%.2lf,%.2lf>\n",x,y);
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
//half-plane-intersection; naive;
const int N=100+1;
int n;
Point points[N],newPoints[N];
void rebuild(const Point &a, const Point &b) {
  points[n] = points[0];
  int m = 0;
  for (int i = 0; i < n; ++ i) {
    double s_1 = det(b - a, points[i + 1] - a);
    double s_2 = det(b - a, points[i] - a);
    if (signum(s_1) * signum(s_2) < 0) {
      newPoints[m ++] = (points[i + 1] * s_2 - points[i] * s_1) / (s_2 - s_1);
    }
    if (signum(det(b - a, points[i + 1] - a)) >= 0) {
      newPoints[m ++] = points[i + 1];
    }
  }
  n = m;
  copy(newPoints, newPoints + n, points);
}
int pointCount;
Point convexHull[N];
bool check(double radius) {
  points[0]=Point(0.0,0.0);
  points[1]=Point(10000.0,0.0);
  points[2]=Point(10000.0,10000.0);
  points[3]=Point(0.0,10000.0);
  n=4;
  for(int i=0; i<pointCount; ++i) {
    Point add=(convexHull[i+1]-convexHull[i]).rotate();
    add=(add.normalize())*radius;
    rebuild(convexHull[i]+add,convexHull[i+1]+add);
    if(n==0) {
      return false;
    }
  }
  return true;
}
double bs(double l,double r) {
  while(r-l>EPSILON) {
    double m=(l+r)/2.0;
    if(check(m)) {
      l=m;
    } else {
      r=m;
    }
  }
  return (l+r)/2.0;
}
int main() {
  while(scanf("%d",&pointCount),pointCount) {
    for(int i=0; i<pointCount; ++i) {
      scanf("%lf%lf",&convexHull[i].x,&convexHull[i].y);
    }
    convexHull[pointCount]=convexHull[0];
    double radius=bs(0.0,5000.0);
    printf("%.6lf\n",radius);
  }
}
