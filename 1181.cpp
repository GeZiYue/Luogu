#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int a;
int main(){
	int n,m,i,now,sum;
	cin>>n>>m;
	now=0;
	sum=1;
	for(i=1;i<=n;i++){
		cin>>a;
		now+=a;
		if(now>m){
			now=a;
			sum++;
		}
	}
	cout<<sum<<endl;
	return 0;
}

