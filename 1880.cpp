#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib> 
#include<algorithm>
using namespace std;
int a[205],dp1[205][205],dp2[205][205],sum[205];
int main(){
	int n,l,i,j,k,maxi=-2147483647,mini=2147483647;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		a[n+i]=a[i];
	}
	for(i=1;i<=n*2;i++){
		sum[i]=sum[i-1]+a[i];
	}
	for(l=2;l<=n;l++){
		for(i=1;i<=(n*2-l+1);i++){
			j=i+l-1;
			for(k=i;k<j;k++){
				if(dp1[i][j]==0){
					dp1[i][j]=dp1[i][k]+dp1[k+1][j]+(sum[j]-sum[i-1]);
				}else{
					dp1[i][j]=max(dp1[i][j],dp1[i][k]+dp1[k+1][j]+(sum[j]-sum[i-1]));
				}
				if(dp2[i][j]==0){
					dp2[i][j]=dp2[i][k]+dp2[k+1][j]+(sum[j]-sum[i-1]);
				}else{
					dp2[i][j]=min(dp2[i][j],dp2[i][k]+dp2[k+1][j]+(sum[j]-sum[i-1]));
				}
			}
			if(l==n){
				maxi=max(maxi,dp1[i][j]);
				mini=min(mini,dp2[i][j]);
			}
		}
	}
	cout<<mini<<endl<<maxi<<endl;
	return 0;

}

