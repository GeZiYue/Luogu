#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<fstream>
using namespace std;
int ans=0,n,m;
int a[10005]={0};
int dp[10005][105];
int main(){
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==2){
			a[i]=0;
		}
	}
	for(i=1;i<=n;i++){
    	dp[i][0]=dp[i-1][0]+(a[i]==1);
	}
 	for(i=1;i<=n;i++){
   		for(j=1;j<=m;j++){
		    dp[i][j]=max(dp[i-1][j-1],dp[i-1][j]);
	  		dp[i][j]+=!(j%2==a[i]);
     	}
 		for (j=0;j<=m;j++){
   			ans=max(ans,dp[n][j]);
		}
	}
	cout<<ans<<endl;
	return 0;

}

