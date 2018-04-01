#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
typedef long long ll;
ll dp[1005];
int main(){
	ll n,i,j;
	cin>>n;
	dp[1]=1;
	for(i=2;i<=n;i++){
		dp[i]=1;
		for(j=1;2*j<=i;j++){
			dp[i]+=dp[j];
		}
	}
	cout<<dp[n]<<endl;
	return 0;
}

