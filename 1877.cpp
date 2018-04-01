#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
bool dp[55][1005];
int main(){
	int n,m,a,i,j,maxi=0;
	cin>>n>>a>>m;
	dp[0][a]=1;
	for(i=1;i<=n;i++){
		cin>>a;
		for(j=a;j<=m;j++){
			if(dp[i-1][j-a]){
				dp[i][j]=1;
				if(i==n){
					maxi=max(maxi,j);
				}
			}
		}
		for(j=0;j+a<=m;j++){
			if(dp[i-1][j+a]){
				dp[i][j]=1;
				if(i==n){
					maxi=max(maxi,j);
				}
			}
		}
	}
	if(maxi==0){
		maxi=-1;
	}
	cout<<maxi<<endl;
	return 0;
}

