#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
string a[25],b;
int main(){
	int n,m,i,j,ans=0;
	cin>>n>>m;
	getline(cin,a[0]);
	for(i=1;i<=n;i++){
		getline(cin,a[i]);
		if(a[i][a[i].size()-1]!=13){
			a[i]+=(char)13;
		}
	}
	for(i=1;i<=m;i++){
		getline(cin,b);
		if(b[b.size()-1]!=13){
			b+=(char)13;
		}
		for(j=1;j<=n;j++){
			if(a[j]==b){
				ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

