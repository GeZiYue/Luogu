#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[2005][2005];
int main(){
	string a,b;
	int n,m,i,j;
	cin>>a>>b;
	n=a.size();
	m=b.size();
	for(i=1;i<=n;i++){
		dp[i][0]=i;
	}
	for(j=1;j<=m;j++){
		dp[0][j]=j;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(a[i-1]==b[j-1]){
				dp[i][j]=dp[i-1][j-1];
			}else{
				dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
			}
		}
	}
	cout<<dp[n][m]<<endl;
	return 0;
}

