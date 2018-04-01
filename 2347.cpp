#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int x[10]={0,1,2,3,5,10,20};
bool dp[1005];
int main(){
	int a,b,i,j,k,n,ans=0;
	n=6;
	dp[0]=1;
	for(i=1;i<=n;i++){
		cin>>a;
		b=x[i];
		for(j=1;j<=a;j++){
			for(k=1000;k>=b;k--){
				if(dp[k]==0&&dp[k-b]==1){
					ans++;
					dp[k]=1;
				}
			}
		}
	}
	cout<<"Total="<<ans<<endl;
	return 0;
}

