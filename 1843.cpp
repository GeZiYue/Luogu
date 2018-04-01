#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
long long a[500005];
int main(){
	long long n,k,m,i,L,R,M,now;
	bool flag;
	cin>>n>>k>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	L=0;
	R=500005;
	while(L<=R){
		M=(L+R)/2;
		now=0;
		flag=1;
		for(i=1;i<=n;i++){
			int l=a[i]-M*k;
			if(l>0){
				now+=l/m+(bool)(l%m);
			}
			if(now>M){
				flag=0;
				break;
			}
		}
		if(flag){
			R=M-1;
		}else{
			L=M+1;
		}
	}
	cout<<R+1<<endl;
	return 0;
}

