#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
long long dp[1005][1005],a[1005],b[1005];
int main(){
    int n,m,i,j;
    cin>>n>>m;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    for(i=1;i<=m;i++){
        cin>>b[i];
    }
    for(i=1;i<=n;i++){
        dp[i][i]=dp[i-1][i-1]+a[i]*b[i];
    }
    for(i=1;i<=n;i++){
        for(j=i+1;j<=m-(n-i);j++){
            dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+a[i]*b[j]);
        }
    }
    cout<<dp[n][m]<<endl;
}
