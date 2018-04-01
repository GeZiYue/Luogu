#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int a[50][50];
int main(){
    int n,i,j,x,y,l1,l2;
    cin>>n;
    for(i=1,x=1,y=(n+1)/2;i<=n*n;i++){
        a[x][y]=i;
        l1=x;
        l2=y;
        x--;
        y++;
        if(x==0){
            x=n;
        }
        if(y==(n+1)){
            y=1;
        }
        if(a[x][y]!=0){
            x=l1+1;
            y=l2;
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            cout<<a[i][j]<<' ';
        }
        cout<<endl;
    }
}
