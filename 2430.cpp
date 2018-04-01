#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int dp[5005],t[5005],a[5005],b[5005]; 
int main(){
	int i,j,x,n,m,k,maxi=0;
	cin>>i>>j;
	x=j/i;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		cin>>t[i];
	}
	for(i=1;i<=n;i++){
		cin>>j>>b[i];
		a[i]=t[j]*x;
	}
	cin>>k;
	for(i=1;i<=n;i++){
		for(j=k;j>=a[i];j--){
			dp[j]=max(dp[j],dp[j-a[i]]+b[i]);
			maxi=max(maxi,dp[j]);
		}
	}
	cout<<maxi<<endl;
	return 0;
}

