#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int a[1005],dp[1005];
int main(){
	int n,i,j,maxi=0;
	cin>>n;
	for(i=1;i<=n;i++){
		a[i]=0;
		for(j=1;j*j<=i;j++){
			if(j*j==i){
				a[i]+=j;
			}else{
				if(i%j==0){
					a[i]+=j;
					a[i]+=i/j;
				}
			}
		}
		a[i]-=i;
	}
	for(i=1;i<=n;i++){
		for(j=n;j>=i;j--){
			dp[j]=max(dp[j],dp[j-i]+a[i]);
			maxi=max(maxi,dp[j]);
		}
	}
	cout<<maxi<<endl;
	return 0;
}

