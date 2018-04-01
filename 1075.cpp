#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int n,i;
	cin>>n;
	for(i=2;i<=n;i++){
		if(n%i==0){
			cout<<n/i<<endl;
			return 0;
		}
	}
	return 0;
}

