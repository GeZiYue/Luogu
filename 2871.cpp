#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[15005];
int main(){
	int n,m,i,j,a,b,ans=0;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a>>b;
		for(j=m;j>=a;j--){
			dp[j]=max(dp[j],dp[j-a]+b);
			ans=max(ans,dp[j]);
		}
	}
	cout<<ans<<endl;
	return 0;
}

