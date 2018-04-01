#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[2005][2005],a[2005];
int main(){
	int n,l,i,j;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		dp[i][i]=a[i]*n;
	}
	for(l=2;l<=n;l++){
		for(i=1;(i+l-1)<=n;i++){
			j=i+l-1;
			dp[i][j]=max(dp[i+1][j]+a[i]*(n-l+1),dp[i][j-1]+a[j]*(n-l+1));
		}
	}
	cout<<dp[1][n]<<endl;
	return 0;
}

