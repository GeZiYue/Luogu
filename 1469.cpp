#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int a[10000005];
int main(){
	int n,i;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(i=1;i<=n;i+=2){
		if(a[i]!=a[i+1]){
			cout<<a[i]<<endl;
			return 0;
		}
	}
	return 0;
}

