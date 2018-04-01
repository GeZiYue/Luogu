#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
#include<iomanip>
using namespace std;
int a[100005];
int main(){
	int n,m,maxi=0,L,R,M,sum,i;
	double l;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>l;
		a[i]=l*100;
		maxi=max(maxi,a[i]);
	}
	L=1;
	R=maxi;
	while(L<=R){
		M=(L+R)/2;
		sum=0;
		for(i=1;i<=n;i++){
			sum+=a[i]/M;
		}
		if(sum>=m){
			L=M+1;
		}else{
			R=M-1;
		}
	}
	cout<<fixed<<setprecision(2)<<R*1.0/100<<endl;
	return 0;
}

