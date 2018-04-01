#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int dp[1000005],a[1000005];
int main(){
	int n,i;
	cin>>n;
	cin>>a[1];
	cin>>a[2];
	for(i=3;i<=n;i++){
		cin>>a[i];
		dp[i]=min(dp[i-1]+a[i],min(dp[i-2]+a[i-1],dp[i-3]+a[i-2]));
	}
	cout<<dp[n]<<endl;
	return 0;
}

