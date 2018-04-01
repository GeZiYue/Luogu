#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
bool dp[105][105][105]={0};
int a[105][105];
int main(){
    int n,m,Mod,i,j,k,ans=0;
    cin>>n>>m>>Mod;
    dp[0][1][1]=true;
    dp[1][0][1]=true;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            cin>>a[i][j];
            a[i][j]%=Mod;
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            for(k=0;k<=Mod;k++){
                if(dp[i-1][j][k]==true||dp[i][j-1][k]==true){
                    dp[i][j][k*a[i][j]%Mod]=true;
                }
            }
        }
    }
    for(k=0;k<=Mod;k++){
        if(dp[n][m][k]==true){
            ans++;
        }
    }
    cout<<ans<<endl;
    for(k=0;k<=Mod;k++){
        if(dp[n][m][k]==true){
            cout<<k<<' ';
        }
    }
    cout<<endl;
}
