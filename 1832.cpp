#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
long long a[1005],dp[1005];
bool t[1005];
int prime(int n){
	int i,j,ans=0;
	for(i=2;i<=n;i++){
		if(t[i]==0){
			a[++ans]=i;
			for(j=2*i;j<=n;j+=i){
				t[j]=1;
			}
		}
	}
	return ans;
}
int main(){
	long long n,m,i,j;
	cin>>n;
	m=prime(n);
	dp[0]=1;
	for(i=1;i<=m;i++){
		for(j=a[i];j<=n;j++){
			dp[j]+=dp[j-a[i]];
		}
	}
	cout<<dp[n]<<endl;
	return 0;
}

