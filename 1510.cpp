#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int dp[10005];
int main(){
	int n,m,k,i,j,a,b,maxi=-1;
	cin>>m>>n>>k;
	for(i=1;i<=n;i++){
		cin>>a>>b;
		for(j=k;j>=b;j--){
			dp[j]=max(dp[j],dp[j-b]+a);
			if(dp[j]>=m){
				maxi=max(maxi,(k-j));
			}
		}
	}
	if(maxi==-1){
		cout<<"Impossible"<<endl;
	}else{
		cout<<maxi<<endl;
	}
	return 0;
}

