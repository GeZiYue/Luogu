#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int main(){
	long long t,n,ans,now;
	cin>>t;
	while(t--){
		ans=0;
		cin>>n;
		now=1;
		while(n){
			ans+=now*(n%10<7?n%10:n%10-1);
			n/=10;
			now*=9;
		}
		cout<<ans<<endl;
	}
	return 0;
}

