/*
poj2540 - Hotter Colder;
Half-plane Intersection;
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
const int N=2000;
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
double calculateArea(void) {
  double area=0.0;
  if(n>=3) {
    points[n]=points[0];
    for(int i=0; i<n; ++i) {
      area+=det(points[i],points[i+1]);
    }
    area*=0.5;
  }
  return area;
}
int main() {
  n=4;
  points[0]=Point(0.0,0.0);
  points[1]=Point(10.0,0.0);
  points[2]=Point(10.0,10.0);
  points[3]=Point(0.0,10.0);
  Point current=Point(0.0,0.0),next;
  char status[7];
  while(scanf("%lf%lf%s",&next.x,&next.y,status)!=EOF) {
    if(status[0]=='S') {
      n=0;
    } else {
      Point midPoint=(current+next)/2.0;
      Point nextPoint=(midPoint+(next-current).rotate());
      if(status[0]=='C') {
        rebuild(midPoint,nextPoint);
      } else {
        rebuild(nextPoint,midPoint);
      }
    }
    current=next;
    printf("%.2lf\n",calculateArea());
  }
}
