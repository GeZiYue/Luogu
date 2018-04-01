#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int a[1000005];
int main(){
	int n,m,i,ans=0,L,M,R;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(i=1;i<n;i++){
		L=i;
		R=n;
		while(L<=R){
			M=(L+R)/2;
			if(a[M]>a[i]+m){
				R=M-1;
			}else{
				L=M+1;
			}
		}
		ans+=(L-i-1);
	}
	cout<<ans<<endl;
	return 0;
}

