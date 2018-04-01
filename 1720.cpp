#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
double a[50];
int main(){
	int n,i;
	cin>>n;
	a[1]=1;
	a[2]=1;
	for(i=3;i<=n;i++){
		a[i]=a[i-1]+a[i-2];
	}
	printf("%.2f",a[n]);
	return 0;
}

