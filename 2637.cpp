#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int a[1005];
int main(){
	int n,m,i,ans1=2147483647,ans2=0;
	cin>>m>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(i=n;i>=(n>m?n-m+1:1);i--){
		if(a[i]*(n-i+1)>=ans2){
			ans1=a[i];
			ans2=a[i]*(n-i+1);
		}
	}
	cout<<ans1<<' '<<ans2<<endl;
	return 0;
}

