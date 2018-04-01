#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int a[105][105];
int xx[10]={0,1,1,1,0,0,-1,-1,-1};
int yy[10]={0,1,0,-1,1,-1,-1,0,1};
int main(){
    int n,m,i,j,k,x,y;
    char s;
    cin>>n>>m;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            cin>>s;
            if(s=='*'){
                a[i][j]=-1;
            }else{
                a[i][j]=0;
            }
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(a[i][j]==-1){
                continue;
            }
            for(k=1;k<=8;k++){
                x=i+xx[k];
                y=j+yy[k];
                if(x<1||y<1||x>n||y>m){
                    continue;
                }
                a[i][j]+=(a[x][y]==-1);
            }
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(a[i][j]==-1){
                cout<<'*';
            }else{
                cout<<a[i][j];
            }
        }
        cout<<endl;
    }
}
