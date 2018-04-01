#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
typedef long long int ll;
ll dp[25][25];
int xx[10]={0,-2,-1,1,2,2,1,-1,-2},yy[10]={0,1,2,2,1,-1,-2,-2,-1};
int main(){
	int n,m,a,b,i,j;
	cin>>n>>m>>a>>b;
	n++;
	m++;
	a++;
	b++;
	for(i=0;i<=8;i++){
		if(a+xx[i]<=n&&a+xx[i]>=1){
			if(b+yy[i]<=m&&b+yy[i]>=1){
				dp[a+xx[i]][b+yy[i]]=-1;
			}
		}
	}
	dp[1][1]=1;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			if(dp[i][j]!=-1){
				if(dp[i-1][j]!=-1){
					dp[i][j]+=dp[i-1][j];
				}
				if(dp[i][j-1]!=-1){
					dp[i][j]+=dp[i][j-1];
				}
			}
		}
	}
	cout<<dp[n][m]<<endl;
	return 0;

}

