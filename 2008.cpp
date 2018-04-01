#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int dp1[10005],dp2[10005],a[10005];
int main(){
	int n,i,j;
	cin>>n;
	cin>>a[1];
	dp1[1]=1;
	dp2[1]=a[1];
	cout<<a[1];
	for(i=2;i<=n;i++){
		cin>>a[i];
		dp1[i]=1;
		dp2[i]=a[i];
		for(j=1;j<i;j++){
			if(a[j]<=a[i]){
				if((dp1[j]+1)>dp1[i]){
					dp1[i]=dp1[j]+1;
					dp2[i]=dp2[j]+a[i];
				}
			}
		}
		cout<<' '<<dp2[i];
	}
	cout<<endl;
	return 0;
}

