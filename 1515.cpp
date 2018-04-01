#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int a[50]={0,0,990,1010,1970,2030,2940,3060,3930,4060,4970,5030,5990,6010,7000},dp[50];
int main(){
	int n,i,j,l,r;
	cin>>l>>r>>n;
	n+=14;
	for(i=15;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	dp[1]=1;
	for(i=2;i<=n;i++){
		j=i-1;
		while(j>=1&&(a[i]-a[j])<l){
			j--;
		}
		for(;(a[i]-a[j])<=r&&j>=1;j--){
			dp[i]+=dp[j];
		}
	}
	cout<<dp[n]<<endl;
}

