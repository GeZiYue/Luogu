#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int a[15],b[15],c[15],dp[155];
int main(){
	int i,j,n,n1,m,k,ans=0,mini=2147483647;
	cin>>n1>>n>>k>>m;
	for(i=1;i<=n1;i++){
		cin>>c[i];
	}
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	for(i=1;i<=n;i++){
		cin>>b[i];
	}
	for(i=1;i<=n;i++){
		for(j=m;j>=a[i];j--){
			dp[j]=max(dp[j],dp[j-a[i]]+b[i]);
			if(dp[j]>=k){
				mini=min(mini,j);
			}
		}
	}
	m-=mini;
	sort(c+1,c+n1+1);
	for(i=1;i<=n;i++){
		if(c[i]<=m){
			m-=c[i];
			ans++;
		}else{
			break;
		}
	}
	cout<<ans<<endl;
}

