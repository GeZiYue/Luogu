#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int l,r,now,ans=0,i;
	cin>>l>>r;
	for(i=l;i<=r;i++){
		now=i;
		while(now){
			if(now%10==2){
				ans++;
			}
			now/=10;
		}
	}
	cout<<ans<<endl;
	return 0;
}

