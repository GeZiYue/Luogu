#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int t[40],ans[10];
int main(){
	int n,i,j,a,now;
	cin>>n;
	for(i=1;i<=7;i++){
		cin>>a;
		t[a]=1;
	}
	for(i=1;i<=n;i++){
		now=0;
		for(j=1;j<=7;j++){
			cin>>a;
			if(t[a]==1){
				now++;
			}
		}
		ans[now]++;
	}
	for(i=7;i>=1;i--){
		cout<<ans[i]<<' ';
	}
	return 0;
}

