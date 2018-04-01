#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int dp[100005],a[105];
int main(){
	int m,n=0,i,j;
	cin>>m;
	for(i=1;i<=m;i++){
		dp[i]=2147483647;
	}
	for(i=1;i*i*i*i<=m;i++){
		a[++n]=i*i*i*i;
	}
	for(i=1;i<=n;i++){
		for(j=a[i];j<=m;j++){
			dp[j]=min(dp[j],dp[j-a[i]]+1);
		}
	}
	cout<<dp[m]<<endl;
	return 0;
}

