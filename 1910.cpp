#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[1005][1005];
int main(){
	int n,m,k,a,b,c,i,j,l,maxi=0;
	cin>>n>>m>>k;
	for(i=1;i<=n;i++){
		cin>>a>>b>>c;
		for(j=m;j>=b;j--){
			for(l=k;l>=c;l--){
				dp[j][l]=max(dp[j][l],dp[j-b][l-c]+a);
				maxi=max(maxi,dp[j][l]);
			}
		}
	}
	cout<<maxi<<endl;
	return 0;
}

