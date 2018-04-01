#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
const long long int Inf=1LL<<62;
using namespace std;
long long int x[5005],y[5005],dp[5005];
long long int gabs(long long int a){
	return a<=0?-a:a;
}
int main(){
	long long int n,m,i,j;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>x[i];
	}
	cin>>m;
	for(i=1;i<=m;i++){
		cin>>y[i];
	}
	sort(x+1,x+n+1);
	sort(y+1,y+m+1);
	for(i=0;i<=m;i++){
		dp[i]=Inf;
	}
	dp[1]=gabs(x[1]-y[1]);
	for(i=2;i<=n;i++){
		for(j=m;j>=1;j--){
			dp[j]=min(dp[j],dp[j-1])+gabs(x[i]-y[j]);
		}
	}
	cout<<dp[m];
	return 0;
}

