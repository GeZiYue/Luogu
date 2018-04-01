#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
double dp[1250][1250];
int main(){
	int n,i,j;
	cin>>n;
	n/=2;
	for(i=2;i<=n;i++){
		dp[i][0]=dp[0][i]=1;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			dp[i][j]=(dp[i-1][j]+dp[i][j-1])*0.5;
		}
	}
	cout<<fixed<<setprecision(4)<<dp[n][n]<<endl;
	return 0;
}

