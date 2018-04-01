#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int f[105][105],a[105][105],n;
int xx[10]={0,1,-1,0,0};
int yy[10]={0,0,0,1,-1};
void DFS(int x,int y,bool flag,int sum,int colour);
int main(){
    int m,i,j,x,y,c;
    cin>>n>>m;
    for(i=1;i<=m;i++){
        cin>>x>>y>>c;
        a[x][y]=c+1;
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            f[i][j]=2147483647;
        }
    }
    DFS(1,1,0,0,a[1][1]);
    if(f[n][n]==2147483647){
        f[n][n]=-1;
    }
    cout<<f[n][n]<<endl;
    return 0;
}
void DFS(int x,int y,bool flag,int sum,int colour){
    if(sum>=f[x][y]){
        return;
    }else{
        f[x][y]=sum;
    }
    if(x==n&&y==n){
        return;
    }
    int i,j,k;
    for(k=1;k<=4;k++){
        i=x+xx[k];
        j=y+yy[k];
        if(i<1||j<1||i>n||j>n){
            continue;
        }
        if(a[i][j]==colour){
            DFS(i,j,0,sum,colour);
        }else{
            if(a[i][j]==0){
                if(flag==0){
                    DFS(i,j,1,sum+2,colour);
                }else{
                    continue;
                }
            }else{
                DFS(i,j,0,sum+1,a[i][j]);
            }
        }
    }
    return;
}
