#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int set(int a,int b,int c){
	return a*100+b*10+c;
}
int main(){
	int n,i,a,b,c,d,e;
	bool flag=0;
	cin>>n;
	for(i=10000;i<=30000;i++){
		a=i/10000;
		b=i/1000%10;
		c=i/100%10;
		d=i/10%10;
		e=i%10;
		if(set(a,b,c)%n==0&&set(b,c,d)%n==0&&set(c,d,e)%n==0){
			cout<<i<<endl;
			flag=1;
		}
	}
	if(flag==0){
		cout<<"No"<<endl;
	}
	return 0;
}

