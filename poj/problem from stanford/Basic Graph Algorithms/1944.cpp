/*
poj1944 - Fiber Communications;
Segment Tree;
*/
#include<cstdio>
#include<vector>
#include<algorithm>
#define pb push_back
using namespace std;
struct SegmentTreeNode {
  int cover,count;
} tree[1<<12];
vector<int> segment[1000];
void construct(int l,int r,int rt) {
  tree[rt].cover=tree[rt].count=0;
  if(l!=r) {
    int m=(l+r)>>1;
    construct(l,m,rt<<1);
    construct(m+1,r,rt<<1|1);
  }
}
void update(int l,int r,int rt) {
  if(tree[rt].cover>0) {
    tree[rt].count=r-l+1;
  } else {
    if(l==r) {
      tree[rt].count=0;
    } else {
      tree[rt].count=tree[rt<<1].count+tree[rt<<1|1].count;
    }
  }
}
void modify(int sl,int sr,int sign,int l,int r,int rt) {
  if(sl>r||sr<l) {
    return ;
  } else {
    if(sl<=l&&r<=sr) {
      tree[rt].cover+=sign;
    } else {
      int m=(l+r)>>1;
      modify(sl,sr,sign,l,m,rt<<1);
      modify(sl,sr,sign,m+1,r,rt<<1|1);
    }
    update(l,r,rt);
  }
}
int query(int sl,int sr,int l,int r,int rt) {
  if(sl>r||sr<l) {
    return 0;
  } else {
    if(sl<=l&&r<=sr) {
      return tree[rt].count;
    } else {
      int m=(l+r)>>1;
      return query(sl,sr,l,m,rt<<1)+query(sl,sr,m+1,r,rt<<1|1);
    }
  }
}
int main() {
  int n,count;
  scanf("%d%d",&n,&count);
  construct(1,2*(n-1),1);
  for(int i=0; i<count; ++i) {
    int x,y,l,r;
    scanf("%d%d",&x,&y);
    l=min(x,y);
    r=max(x,y);
    segment[l].pb(r);
    modify(l,r-1,+1,1,2*(n-1),1);
  }
  int result=query(1,n-1,1,2*(n-1),1);
  for(int i=1; i<n; ++i) {
    for(int j=0; j<segment[i].size(); ++j) {
      int l=i;
      int r=segment[i][j];
      modify(l,r-1,-1,1,2*(n-1),1);
      modify(r,n+l-1,+1,1,2*(n-1),1);
      if(r<=n-1) {
        segment[r].pb(n+l);
      }
    }
    result=min(result,query(i+1,i+n-1,1,2*(n-1),1));
  }
  printf("%d\n",result);
}
