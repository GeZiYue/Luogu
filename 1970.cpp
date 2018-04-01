#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int dp1[100005],dp2[100005];
int main(){
	int n,i,a,b;
	cin>>n;
	cin>>a;
	dp1[1]=1;
	dp2[1]=1;
	for(i=2;i<=n;i++){
		cin>>b;
		if(a<b){
			dp1[i]=dp2[i-1]+1;
		}else{
			dp1[i]=dp1[i-1];
		}
		if(a>b){
			dp2[i]=dp1[i-1]+1;
		}else{
			dp2[i]=dp2[i-1];
		}
		a=b;
	}
	cout<<max(dp1[n],dp2[n])<<endl;
	return 0;
}

