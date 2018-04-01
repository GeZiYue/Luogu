#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[105][105],a[105][105];
int main(){
	int n,m,i,j,ans=-1;
	cin>>n>>m;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            cin>>a[i][j];
			dp[i][j]=a[i][j];
    	}
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(a[i][j]){
            	dp[i][j]=min(dp[i-1][j],min(dp[i-1][j-1],dp[i][j-1]))+1;
				ans=max(dp[i][j],ans);
			}
		}
	}
    cout<<ans;
	return 0;
}

