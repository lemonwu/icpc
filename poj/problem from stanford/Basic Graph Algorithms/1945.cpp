/*
poj1945 - Power Hungry Cows;
bfs;
*/
#include<cstdio>
#include<algorithm>
using namespace std;
int next[8][4]= {
  {0,1,0,2},{0,1,2,0},{0,1,1,1},{0,1,-1,1},
  {1,0,0,2},{1,0,2,0},{1,0,1,1},{1,0,-1,1}
};
bool visited[200][30000];
const int N=(int)(1e7);
int x[N],y[N],d[N];
int bfs(int target) {
  for(int i=0; i<200; ++i) {
    for(int j=0; j<30000; ++j) {
      visited[i][j]=false;
    }
  }
  int head=0,tail=1;
  x[0]=0,y[0]=1,d[0]=0;
  visited[0][1]=true;
  while(head!=tail) {
    for(int i=0; i<8; ++i) {
      int xx=x[head]*next[i][0]+y[head]*next[i][1];
      int yy=x[head]*next[i][2]+y[head]*next[i][3];
      if(xx>yy) {
        swap(xx,yy);
      }
      if(xx>=200||yy>=30000) {
        continue;
      }
      if(visited[xx][yy]) {
        continue;
      }
      visited[xx][yy]=true;
      x[tail]=xx,y[tail]=yy,d[tail]=d[head]+1;
      if(xx==target||yy==target) {
        return d[tail];
      }
      tail++;
    }
    head++;
  }
}
int main() {
  int target;
  scanf("%d",&target);
  printf("%d\n",bfs(target));
}
