#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
#include<map>
using namespace std;
map<int,int>ans;
long long a[100005];
int main(){
	long long n,m,i,s=0;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
		ans[a[i]]++;
	}
	for(i=1;i<=n;i++){
		s+=ans[a[i]+m];
	}
	cout<<s<<endl;
	return 0;
}

