#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[205][205];
int main(){
	int n,m,t,i,j,k,a,b,ans=0;
	cin>>n>>m>>t;
	for(i=1;i<=n;i++){
		cin>>b>>a;
		for(j=m;j>=a;j--){
			for(k=t;k>=b;k--){
				dp[j][k]=max(dp[j][k],dp[j-a][k-b]+1);
				ans=max(ans,dp[j][k]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

