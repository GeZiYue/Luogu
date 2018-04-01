#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[35000][5];
int main(){
    int t,n,i,j,k,m=32768;
    dp[0][0]=1;
    for(i=1;i*i<=m;i++){
        for(j=i*i;j<=m;j++){
            for(k=1;k<=4;k++){
                dp[j][k]+=dp[j-i*i][k-1];
            }
        }
    }
    cin>>t;
    while(t--){
        cin>>n;
        cout<<dp[n][1]+dp[n][2]+dp[n][3]+dp[n][4]<<endl;
    }
}
