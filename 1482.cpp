#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int gcd(int a,int b);
int main(){
	int a,b,c,d;
	char t;
	cin>>a>>t>>b>>c>>t>>d;
	c*=a;
	d*=b;
	int s=gcd(c,d);
	cout<<(d/s)<<' '<<(c/s);
	return 0;
}
int gcd(int a,int b){
	if(b==0){
		return a;
	}
	return gcd(b,a%b);
}

