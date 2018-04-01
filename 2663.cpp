#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int a[105];
bool dp[10005];
int main(){
	int n,i,j,k,sum=0,ans=0;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	sum/=2;
	dp[0]=1;
	for(i=1;i<=n;i++){
		for(k=sum;k>=a[i];k--){
			if(dp[k-a[i]]){
				dp[k]=1;
			}
			if(dp[k]){
				ans=max(ans,k);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

