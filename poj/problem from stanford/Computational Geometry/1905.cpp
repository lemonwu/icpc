/*
poj1905 - Expanding Rods;
Binary Search;
*/
#include<cstdio>
#include<cmath>
const double eps=1e-4;
double L1,L2,N,C;
double bs(double l,double r) {
  while(r-l>eps) {
    double m=(l+r)/2.0;
    double R=(L1*L1/4.0+m*m)/(2.0*m);
    double alpha=asin(L1/(2.0*R));
    if(R*alpha*2.0<L2) {
      l=m;
    } else {
      r=m;
    }
  }
  return (l+r)/2.0;
}
int main() {
  while(scanf("%lf%lf%lf",&L1,&N,&C)==3&&L1>=0.0) {
    L2=(1+N*C)*L1;
    double result=bs(0.0,L1/2.0);
    printf("%.3lf\n",result);
  }
}
