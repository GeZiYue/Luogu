#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Mod 9999973
#define add(a,b) a=(a+b)%Mod
#define ll unsigned long long int
ll dp[105][105][105];
int main(){
    ll n,m,i,j,k,l;
    ll ans=0;
    cin>>n>>m;
    dp[0][0][0]=1;
    for(i=0;i<=n;i++){
        for(j=0;j<=m;j++){
            for(k=0;k<=m;k++){
                if(dp[i][j][k]){
                    l=m-j-k;
                    add(dp[i+1][j][k],dp[i][j][k]);
                    if(l>0){
                        add(dp[i+1][j+1][k],dp[i][j][k]*l);
                    }
                    if(j>0){
                        add(dp[i+1][j-1][k+1],dp[i][j][k]*j);
                    }
                    if(l>1){
                        add(dp[i+1][j+2][k],dp[i][j][k]*l*(l-1)/2);
                    }
                    if(j>1){
                        add(dp[i+1][j-2][k+2],dp[i][j][k]*j*(j-1)/2);
                    }
                    if(l>0&&j>0){
                        add(dp[i+1][j][k+1],dp[i][j][k]*l*j);
                    }
                    if(i==n){
                        add(ans,dp[i][j][k]);
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
