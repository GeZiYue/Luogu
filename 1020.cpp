#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int a[100005],dp[100005];
int main(){
	int n=0,i,len;
	while(cin>>a[++n]){}
	n--;
	len=1;
	dp[1]=a[1];
	for(i=2;i<=n;i++){
		if(a[i]<=dp[len]){
			dp[++len]=a[i];
		}else{
			dp[lower_bound(dp+1,dp+len+1,a[i],[](int x,int y){
				return x>=y;
			})-dp]=a[i];
		}
	}
	cout<<len<<endl;
	len=1;
	dp[1]=a[1];
	for(i=2;i<=n;i++){
		if(a[i]>dp[len]){
			dp[++len]=a[i];
		}else{
			dp[lower_bound(dp+1,dp+len+1,a[i],[](int x,int y){
				return x<y;
			})-dp]=a[i];
		}
	}
	cout<<len<<endl;
	return 0;
}
