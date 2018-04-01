#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int sum[3005];
int main(){
	int n,m,a,i,mini=2147483647;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a;
		sum[i]=sum[i-1]+a;
	}
	for(i=m;i<=n;i++){
		mini=min(mini,(sum[i]-sum[i-m]));
	}
	cout<<mini<<endl;
	return 0;
}

