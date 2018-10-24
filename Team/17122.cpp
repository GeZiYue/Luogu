#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int n,len=0,i;
	cin>>n;
	n++;
	i=1;
	while(i<=n){
		len++;
		i*=2;
	}
	len--;
	for(i=len;i>=1;i--){
		cout<<((n&(1<<(i-1)))?7:4);
	}
	cout<<endl;
	return 0;
}

