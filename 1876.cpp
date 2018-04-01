#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int n,i;
	cin>>n;
	for(i=1;i*i<=n;i++){
		cout<<i*i<<' ';
	}
	return 0;
}

