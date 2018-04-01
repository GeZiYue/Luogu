#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
typedef long long int ll;
ll dp[2005][2005],a[2005][2005];
int main(){
	ll n,m,i,j,ans=2147483647;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			cin>>a[i][j];
			dp[i][j]=2147483647;
		}
	}
	for(i=1;i<=n;i++){
		dp[i][1]=min(dp[i-1][1],dp[i-1][m])+a[1][i];
		if(i==n){
			ans=min(ans,dp[i][1]);
		}
		for(j=2;j<=m;j++){
			dp[i][j]=min(dp[i-1][j],dp[i-1][j-1])+a[j][i];
			if(i==n){
				ans=min(ans,dp[i][j]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

