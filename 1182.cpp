#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int a[100005];
int main(){
	int n,m,i,L,R,M,now,sum;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	L=1;
	R=1000000000;
	while(L<R){
		M=(L+R)/2;
		now=0;
		sum=1;
		for(i=1;i<=n;i++){
			now+=a[i];
			if(a[i]>M){
				sum=m;
			}
			if(now>M){
				now=a[i];
				sum++;
			}
		}
		if(sum<=m){
			R=M;
		}else{
			L=M+1;
		}
	}
	cout<<L<<endl;
	return 0;
}

