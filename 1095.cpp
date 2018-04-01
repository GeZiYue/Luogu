#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[300005];
int main(){
	int k,n,m,i;
	cin>>k>>m>>n;
	for(i=1;i<=n;i++){
		if(k>=10){
			dp[i]=dp[i-1]+60;
			k-=10;
		}else{
			dp[i]=dp[i-1];
			k+=4;
		}
	}
	for(i=1;i<=n;i++){
		dp[i]=max(dp[i],dp[i-1]+17);
		if(dp[i]>=m){
			cout<<"Yes"<<endl<<i<<endl;
			return 0;
		}
	}
	cout<<"No"<<endl<<dp[n]<<endl;
	return 0;
}

