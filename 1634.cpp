#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
typedef unsigned long long int ll;
int main(){
	ll n,k,i,ans=1;
	cin>>n>>k;
	for(i=1;i<=k;i++){
		ans*=(n+1);
	}
	cout<<ans<<endl;
	return 0;
}

