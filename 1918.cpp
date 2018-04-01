#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
#include<map>
using namespace std;
map<int,int>a;
int main(){
	int n,m,i,l;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>l;
		a[l]=i;
	}
	cin>>m;
	for(i=1;i<=m;i++){
		cin>>l;
		cout<<a[l]<<endl;
	}
	return 0;
}

