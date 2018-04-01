#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int dp[405][405];
int main(){
	int n,m,k,a,b,c,i,j,l,maxi;
	cin>>m>>k>>n;
	for(i=1;i<=n;i++){
		cin>>a>>b>>c;
		for(j=m;j>=a;j--){
			for(l=k;l>=b;l--){
				dp[j][l]=max(dp[j][l],dp[j-a][l-b]+c);
			}
		}
	}
	cout<<dp[m][k]<<endl;
	return 0;
}

