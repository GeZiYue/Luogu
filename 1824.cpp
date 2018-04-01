#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int a[100005];
int main(){
    int n,m,i,L,M,R,now,maxi=0,ans;
    cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
		maxi=max(maxi,a[i]);
	}
	sort(a+1,a+n+1);
	L=1;
	R=maxi;
	while(L<R){
		M=(L+R)/2;
		now=0;
		ans=1;
		for(i=2;i<=n;i++){
			now+=a[i]-a[i-1];
			if(now>=M){
				now=0;
				ans++;
			}
		}
		if(ans>=m){
			L=M+1;
		}else{
			R=M;
		}
	}
	cout<<L-1<<endl;
	return 0;
}

