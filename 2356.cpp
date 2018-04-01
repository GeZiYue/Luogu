#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int a[1005][1005],b[1005],c[1005];
int main(){
	int n,i,j,maxi=-1;
	cin>>n;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			cin>>a[i][j];
			b[i]+=a[i][j];
			c[j]+=a[i][j];
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(a[i][j]==0){
				maxi=max(maxi,b[i]+c[j]);
			}
		}
	}
	if(maxi==-1){
		cout<<"Bad Game!"<<endl;
	}else{
		cout<<maxi<<endl;
	}
	return 0;
}

