#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int n,i,t;
	string a;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a;
		t=a.size();
		if((a[t-1]-'0')%2==1){
			cout<<"odd"<<endl;
		}else{
			cout<<"even"<<endl;
		}
	}
	return 0;
}

