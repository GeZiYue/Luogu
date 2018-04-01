#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[10005];
int main(){
	int n,m,i,j,a,b,ans=0;
	cin>>m>>n;
	for(i=1;i<=n;i++){
		cin>>b>>a;
		for(j=a;j<=m;j++){
			dp[j]=max(dp[j],dp[j-a]+b);
			ans=max(ans,dp[j]);
		}
	}
	cout<<ans<<endl;
	return 0;
}

