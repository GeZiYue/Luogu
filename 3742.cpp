#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	string a,b;
	int n,i;
	cin>>n;
	cin>>a>>b;
	for(i=0;i<n;i++){
		if(b[i]>a[i]){
			cout<<-1<<endl;
			return 0;
		}
	}
	cout<<b<<endl;
	return 0;
}

