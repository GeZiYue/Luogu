#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
typedef long long int ll;
ll a[50];
int main(){
	ll n,i,t;
	bool flag=1;
	cin>>n;
	a[1]=1;
	a[2]=1;
	for(i=3;i<=n;i++){
		a[i]=(a[i-2]+a[i-1])%(1<<31);
	}
	t=a[n];
	cout<<t<<'=';
	for(i=2;i*i<=t;i++){
		while(t%i==0){
			if(flag){
				printf("%d",i);
				flag=0;
			}else{
				printf("*%d",i);
			}
			t/=i;
		}
	}
	if(t>1){
		if(flag){
			cout<<t;
		}else{
			cout<<'*'<<t;
		}
	}
	cout<<endl;
	return 0;
}

