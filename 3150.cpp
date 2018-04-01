#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int t,n;
	cin>>t;
	while(t--){
		cin>>n;
		if(n&1){
			cout<<"zs ";
		}else{
			cout<<"pb ";
		}
		cout<<"wins"<<endl;
	}
	return 0;
}

