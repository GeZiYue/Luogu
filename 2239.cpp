#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int n,a,b,i,j,sum=0,k1,k2,k3,k4;
	cin>>n>>a>>b;
	for(i=1,j=n-1;;i++,j-=2){
		if(a==i||b==i||a==(n-i+1)||b==(n-i+1)){
			break;
		}else{
			sum+=j*4;
		}
	}
	sum++;
	k1=i;
	k2=i;
	k3=n-i+1;
	k4=n-i+1;
	if(a==k1){
		cout<<sum+(b-k2)<<endl;
	}else{
		if(b==k4){
			cout<<sum+j+(a-k1)<<endl;
		}else{
			if(a==k3){
				cout<<sum+2*j+(k4-b)<<endl;
			}else{
				cout<<sum+3*j+(k3-a)<<endl;
			}
		}
	}
	return 0;
}
