/*
poj1584 - A Round Peg in a Ground Hole;
Convex Hull; Circle;
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
  double to(const Point &a, const Point &b) const;
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
double Point::to(const Point &a, const Point &b) const {
  Point p = *this;
  return abs(det(p - a, p - b) / (a - b).norm());
}
const int N=1000;
int n;
Point peg,point[N];
double pegRadius;
bool isConvexHull(void) {
  int sign=-2;
  for(int i=0; i<n; ++i) {
    int temp=signum(det(point[(i-1+n)%n]-point[i],point[i]-point[(i+1)%n]));
    if(sign==-2) {
      if(temp) {
        sign=temp;
      }
    } else {
      if(sign*temp<0) {
        return false;
      }
    }
  }
  if(sign==-2) {
    return false;
  } else {
    return true;
  }
}
bool isInConvexHull(void) {
  int sign=-2;
  for(int i=0; i<n; ++i) {
    int temp=signum(det(point[i]-peg,point[(i+1)%n]-peg));
    if(sign==-2) {
      sign=temp;
    } else {
      if(sign*temp<=0) {
        return false;
      }
    }
    if(signum(pegRadius-peg.to(point[i],point[(i+1)%n]))>0) {
      return false;
    }
  }
  return true;
}
int main() {
  while(scanf("%d",&n),n>=3) {
    scanf("%lf%lf%lf",&pegRadius,&peg.x,&peg.y);
    for(int i=0; i<n; ++i) {
      scanf("%lf%lf",&point[i].x,&point[i].y);
    }
    if(isConvexHull()) {
      if(isInConvexHull()) {
        puts("PEG WILL FIT");
      } else {
        puts("PEG WILL NOT FIT");
      }
    } else {
      puts("HOLE IS ILL-FORMED");
    }
  }
}
