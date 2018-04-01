#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
void gwork(int n);
int l2(int n);
int main(){
	int n;
	cin>>n;
	gwork(n);
	return 0;
}
void gwork(int n){
	int l=n,i;
	bool flag=1;
	while(l){
		if(flag==1){
			flag=0;
		}else{
			cout<<"+";
		}
		i=l2(l);
		if(i==0){
			cout<<"2(0)";
		}else{
			if(i==1){
				cout<<"2";
			}else{
				cout<<"2(";
				gwork(i);
				cout<<")";
			}
		}
		l-=(1<<i);
	}
	return;
}
int l2(int n){
	int l=n,sum=0;
	while(l>=2){
		sum++;
		l/=2;
	}
	return sum;
}
