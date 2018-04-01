#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int dp[205];
int main(){
	int n,i,j,a;
	cin>>n;
	for(i=2;i<=n;i++){
		dp[i]=2147483647;
	}
	for(i=1;i<=n;i++){
		for(j=i+1;j<=n;j++){
			cin>>a;
			dp[j]=min(dp[j],dp[i]+a);
		}
	}
	cout<<dp[n];
}

