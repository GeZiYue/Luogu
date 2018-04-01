#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int a[5005];
int main(){
	int n,m,maxi=0,L,R,M,sum,i;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
		maxi=max(maxi,a[i]);
	}
	L=1;
	R=maxi;
	while(L<R){
		M=(L+R)/2;
		sum=0;
		for(i=1;i<=n;i++){
			sum+=a[i]/M;
		}
		if(sum>=m){
			L=M+1;
		}else{
			R=M;
		}
	}
	cout<<L-1<<endl;
	return 0;
}

