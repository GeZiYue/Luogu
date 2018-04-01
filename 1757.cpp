#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[2005][2005],x[2005],y[12005];
struct Node{
	int sum;
	int num[2005];
}a[2005];
int main(){
	int n,m,i,j,k,c,l=0,maxi=0;
	cin>>m>>n;
	for(i=1;i<=2000;i++){
		a[i].sum=0;
		memset(a[i].num,0,sizeof(a[i].num));
	}
	for(i=1;i<=n;i++){
		cin>>x[i]>>y[i]>>c;
		l=max(l,c);
		a[c].num[++a[c].sum]=i;
	}
	for(i=1;i<=l;i++){
		for(j=0;j<=m;j++){
			dp[i][j]=dp[i-1][j];
		}
		for(j=1;j<=a[i].sum;j++){
			for(k=m;k>=x[a[i].num[j]];k--){
				dp[i][k]=max(dp[i][k],dp[i-1][k-x[a[i].num[j]]]+y[a[i].num[j]]);
				maxi=max(maxi,dp[i][k]);
			}
		}
	}
	cout<<maxi<<endl;
	return 0;
}

