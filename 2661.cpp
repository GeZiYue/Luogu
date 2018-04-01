#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int a[200005],b[200005],c[200005];
int main(){
	int n,i,j,mini=2147483647,now;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	for(i=1;i<=n;i++){
		now=0;
		for(j=i;b[j]==0;j=a[j]){
			b[j]=i;
			c[j]=++now;
		}
		if(b[j]==i){
			mini=min(mini,now+1-c[j]);
		}
	}
	cout<<mini<<endl;
	return 0;
}
