#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int s[1005],dp[1005];
int main(){
	int n,a,i,j;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a;
		s[i]=s[i-1]+a;
		dp[i]=(a>=0);
	}
	if(s[n]<0){
		cout<<"Impossible"<<endl;
		return 0;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<i;j++){
			if(s[i]-s[j]>=0&&dp[j]>0){
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
	}
	cout<<dp[n]<<endl;
	return 0;
}

