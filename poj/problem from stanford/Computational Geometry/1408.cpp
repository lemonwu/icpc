/*
poj1408 - Fishnet;
line-line-intersection;
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
//line-line-intersection;
Point intersect(const Point &a, const Point &b,const Point &c, const Point &d) {
  double s_1 = det(b - a, c - a);
  double s_2 = det(b - a, d - a);
  return (s_2 * c - s_1 * d) / (s_2 - s_1);
}
const int N=30+2;
int n;
Point point[4][N],temp[5];
double calculateArea(int a,int b) {
  temp[0]=intersect(point[0][b],point[1][b],point[2][a],point[3][a]);
  temp[1]=intersect(point[0][b+1],point[1][b+1],point[2][a],point[3][a]);
  temp[2]=intersect(point[0][b+1],point[1][b+1],point[2][a+1],point[3][a+1]);
  temp[3]=intersect(point[0][b],point[1][b],point[2][a+1],point[3][a+1]);
  temp[4]=temp[0];
  double area=0.0;
  for(int i=0; i<4; ++i) {
    area+=det(temp[i],temp[i+1]);
  }
  area*=0.5;
  return area;
}
int main() {
  while(scanf("%d",&n),n) {
    point[0][0]=Point(0.0,0.0),point[0][n+1]=Point(1.0,0.0);
    for(int i=1; i<=n; ++i) {
      scanf("%lf",&point[0][i].x),point[0][i].y=0.0;
    }
    point[1][0]=Point(0.0,1.0),point[1][n+1]=Point(1.0,1.0);
    for(int i=1; i<=n; ++i) {
      scanf("%lf",&point[1][i].x),point[1][i].y=1.0;
    }
    point[2][0]=Point(0.0,0.0),point[2][n+1]=Point(0.0,1.0);
    for(int i=1; i<=n; ++i) {
      scanf("%lf",&point[2][i].y),point[2][i].x=0.0;
    }
    point[3][0]=Point(1.0,0.0),point[3][n+1]=Point(1.0,1.0);
    for(int i=1; i<=n; ++i) {
      scanf("%lf",&point[3][i].y),point[3][i].x=1.0;
    }
    double result=0.0;
    for(int i=0; i<n+1; ++i) {
      for(int j=0; j<n+1; ++j) {
        result=max(result,calculateArea(i,j));
      }
    }
    printf("%.6lf\n",result);
  }
}
