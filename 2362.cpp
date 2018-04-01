#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int dp1[25],dp2[25],a[25];
int main(){
	int t,n,i,j,maxi,ans,now;
	cin>>t;
	while(t--){
		cin>>n;
		cin>>a[1];
		dp1[1]=dp2[1]=1;
		maxi=1;
		ans=0;
		for(i=2;i<=n;i++){
			cin>>a[i];
			dp1[i]=dp2[i]=1;
			for(j=1;j<i;j++){
				if(a[i]>=a[j]){
					now=dp1[j]+(a[i]>=a[j]);
					if(dp1[i]==now){
						dp2[i]+=dp2[j];
					}else{
						if(dp1[i]<now){
							dp1[i]=now;
							dp2[i]=dp2[j];
						}
					}
				}
			}
			if(dp1[i]==maxi){
				ans+=dp2[i];
			}else{
				if(dp1[i]>maxi){
					maxi=dp1[i];
					ans=dp2[i];
				}
			}
		}
		cout<<maxi<<' '<<ans<<endl;
	}
	return 0;
}

