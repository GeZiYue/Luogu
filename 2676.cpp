#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
typedef long long int ll;
ll a[20005];
bool cmp(ll i,ll j){
	return i>j;
}
int main(){
	ll n,m,i,sum;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	for(i=1,sum=0;sum<=m;i++){
		sum+=a[i];
	}
	cout<<i-1<<endl;
	return 0;
}

