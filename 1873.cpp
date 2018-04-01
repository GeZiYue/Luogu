#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long int ll;
ll a[1000005];
int main(){
	ll n,m,i,L=1,M,R=0,now;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
		R=max(R,a[i]);
	}
	while(L<R){
		M=(L+R)/2;
		now=0;
		for(i=1;i<=n;i++){
			now+=max(0LL,a[i]-M);
		}
		if(now>=m){
			L=M+1;
		}else{
			R=M;
		}
	}
	cout<<L-1<<endl;
	return 0;
}

