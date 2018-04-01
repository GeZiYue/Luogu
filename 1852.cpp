#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[5005][5005];
char a[5005],b[5005];
int main(){
	int n,m,i,j;
	cin>>a+1>>b+1;
	n=strlen(a+1);
	m=strlen(b+1);
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(a[i]==b[j]){
				dp[i][j]=dp[i-1][j-1]+1;
			}else{
				dp[i][j]=max(dp[i-1][j-1],max(dp[i-1][j],dp[i][j-1]));
			}
		}
	}
	cout<<dp[n][m]<<endl;
	return 0;
}

