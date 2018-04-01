#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int a[30005],b[30005],s[30005];
int main(){
	int n,i,ans=2147483647;
	cin>>n;
	a[0]=b[0]=0;
	b[n+1]=0;
	for(i=1;i<=n;i++){
		cin>>s[i];
		s[i]-=1;
		a[i]=a[i-1]+s[i];
	}
	for(i=n;i>=1;i--){
		b[i]=b[i+1]+(!s[i]);
	}
	for(i=0;i<=n;i++){
		ans=min(ans,a[i]+b[i+1]);
	}
	cout<<ans<<endl;
	return 0;
}

