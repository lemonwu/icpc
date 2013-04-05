/*
poj2074 - Line of Sight;
Vector;
*/
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
#define pb push_back
using namespace std;
const double eps=1e-10;
struct Shadow {
  double l,r;
  bool operator<(const Shadow &temp)const {
    if(fabs(l-temp.l)<eps) {
      return r>temp.r+eps;
    } else {
      return l+eps<temp.l;
    }
  }
};
struct Segment {
  double l,r,h;
} house,line,obstructions;
vector<Shadow> shadow;
double calculate(double &x1,double &y1,double &x2,double &y2,double &y3) {
  return x1+(x2-x1)*(y3-y1)/(y2-y1);
}
int main() {
  while(scanf("%lf%lf%lf",&house.l,&house.r,&house.h)) {
    if(house.l==0&&house.r==0&&house.h==0) {
      break;
    } else {
      scanf("%lf%lf%lf",&line.l,&line.r,&line.h);
      shadow.clear();
      int n;
      scanf("%d",&n);
      for(int i=0; i<n; ++i) {
        scanf("%lf%lf%lf",&obstructions.l,&obstructions.r,&obstructions.h);
        if(obstructions.h>line.h+eps&&obstructions.h+eps<house.h) {
          Shadow temp;
          temp.l=calculate(house.r,house.h,obstructions.l,obstructions.h,line.h);
          temp.r=calculate(house.l,house.h,obstructions.r,obstructions.h,line.h);
          if(temp.l+eps<line.r&&temp.r>line.l+eps) {
            temp.l=max(temp.l,line.l);
            temp.r=min(temp.r,line.r);
            shadow.pb(temp);
          }
        }
      }
      sort(shadow.begin(),shadow.end());
      Shadow temp;
      temp.l=temp.r=line.r;
      shadow.pb(temp);
      double result=0.0,current=line.l;
      for(int i=0; i<shadow.size(); ++i) {
        if(shadow[i].l>current+eps) {
          result=max(result,shadow[i].l-current);
        }
        current=max(current,shadow[i].r);
      }
      if(result<eps) {
        puts("No View");
      } else {
        printf("%.2lf\n",result+eps);
      }
    }
  }
}
