#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
char a[1005],b[1005];
int dp[1005][1005];
int main(){
    int n,i,j;
    cin>>a+1;
    n=strlen(a+1);
    for(i=1;i<=n;i++){
        b[i]=a[n-i+1];
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(a[i]==b[j]){
                dp[i][j]=dp[i-1][j-1]+1;
            }else{
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
    }
    cout<<n-dp[n][n]<<endl;
    return 0;
}