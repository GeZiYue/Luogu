#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int n,now,a,i,sum=1,ans=1;
	cin>>n;
	cin>>now;
	for(i=2;i<=n;i++){
		cin>>a;
		if(a>now){
			sum++;
			now=a;
		}else{
			ans=max(ans,sum);
			now=a;
			sum=1;
		}
	}
	ans=max(ans,sum);
	cout<<ans<<endl;
	return 0;
}

