#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int gcd(int a,int b){
	if(b==0){
		return a;
	}else{
		return gcd(b,a%b);
	}
}
int main(){
	int a,b,c;
	cin>>a>>b>>c;
	cout<<min(a,min(b,c))/(gcd(min(a,min(b,c)),max(a,max(b,c))))<<'/'<<max(a,max(b,c))/(gcd(min(a,min(b,c)),max(a,max(b,c))));
	return 0;
}

