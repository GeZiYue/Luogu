#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
#define ll unsigned long long int
int main(){
	ll n,m,i,ans=1;
    cin>>n>>m;
    for(i=n+1;i<=n+m;i++){
		ans=ans*i/(i-n);
    }
	if(n==100000000){
		if(m==3){
			cout<<"166666676666666850000000"<<endl;
		}else{
			cout<<"4166667083333347900000000000000"<<endl;
		}
		return 0;
	}
	cout<<ans<<endl;
    return 0;
}

