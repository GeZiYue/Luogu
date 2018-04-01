#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int a,b,t,i,n;
	cin>>n;
	a=0;
	b=1;
	if(n==1){
		b=0;
	}
	for(i=3;i<=n;i++){
		t=(i-1)*(a+b);
		a=b;
		b=t;
	}
	cout<<b<<endl;
	return 0;
}

