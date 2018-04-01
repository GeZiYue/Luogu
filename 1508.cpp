#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[210][210];
int main(){
	int n,m,i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>dp[i][j];
		}
	}
	for(i=2;i<=n+1;i++){
		for(j=1;j<=m;j++){
			dp[i][j]+=max(dp[i-1][j],max(dp[i-1][j-1],dp[i-1][j+1]));
		}
	}
	cout<<dp[n+1][m/2+1]<<endl;
	return 0;
}

