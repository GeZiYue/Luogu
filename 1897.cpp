#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int a[100005]={0};
bool cmp(int x,int y){
	return x<y;
}
int main(){
	int n,i,ans=0,now=0;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++){
		ans+=(a[i]-now)*10;
		if(a[i]!=a[i-1]){
			ans+=5;
		}
		now=a[i];
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}

