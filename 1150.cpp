#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int n,m,ans=0,l;
	cin>>n>>m;
	ans=n;
	while(n>=m){
		l=n;
		n-=(n/m)*m;
		n+=l/m;
		ans+=l/m;
	}
	cout<<ans<<endl;
	return 0;

}

