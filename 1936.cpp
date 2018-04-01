#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int main(){
	int n,a,b;
	cin>>n;
	a=1;
	b=1;
	while(b<=n){
		b=a+b;
		a=b-a;
	}
	cout<<"m="<<b-a<<endl<<"n="<<a<<endl;
	return 0;
}

