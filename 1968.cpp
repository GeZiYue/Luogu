#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int main(){
	double dp1,dp2,tmp;
	int n,i,a;
	cin>>n;
	dp1=100.0;
	dp2=0;
	for(i=1;i<=n;i++){
		cin>>a;
		tmp=dp1;
		dp1=max(dp1,(dp2/a*100));
		dp2=max(dp2,(tmp/100*a));
	}
	printf("%.2lf",dp1);
	return 0;
}

