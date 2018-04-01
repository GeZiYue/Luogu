#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int dp[50005];
int main(){
	int n,m,a,ans=0,i,j;
	cin>>m>>n;
	for(i=1;i<=n;i++){
		cin>>a;
		for(j=m;j>=a;j--){
			dp[j]=max(dp[j],dp[j-a]+a);
			ans=max(ans,dp[j]);
		}
		if(ans==m){
			break;
		}
	}
	cout<<ans<<endl;
}

