#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int sum[125][125],a[125][125];
int main(){
	int n,i,j,k,dp,ans=0;
	cin>>n;
	for(i=1;i<=n;i++){
		sum[i][0]=0;
		for(j=1;j<=n;j++){
			cin>>a[i][j];
			sum[i][j]=sum[i][j-1]+a[i][j];
		}
	}
	for(i=1;i<=n;i++){
		for(j=i;j<=n;j++){
			dp=0;
			for(k=1;k<=n;k++){
				dp+=sum[k][j]-sum[k][i-1];
				if(dp<0){
					dp=0;
				}
				ans=max(ans,dp);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

