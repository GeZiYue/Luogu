#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long int ll;
ll dp[1005];
int main(){
	ll n,m,i,j,a,b,c;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a>>b>>c;
		for(j=m;j>=0;j--){
			if(j<c){
				dp[j]+=a;
			}else{
				dp[j]=max(dp[j]+a,dp[j-c]+b);
			}
		}
	}
	cout<<dp[m]*5<<endl;
	return 0;
}

