#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
#define INF 2147483647
int dp[105][105],k[105];
int main(){
	int n,i,j,a,b,ans=INF;
	cin>>n;
	for(i=1;i<=100;i++){
		for(j=1;j<=100;j++){
			dp[i][j]=INF;
		}
	}
	for(i=1;i<=n;i++){
		cin>>k[i];
		for(j=1;j<=k[i];j++){
			while(1){
				cin>>a;
				if(a==0){
					break;
				}
				cin>>b;
				dp[i][j]=min(dp[i][j],dp[i-1][a]+b);
			}
			if(i==n){
				ans=min(ans,dp[i][j]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

