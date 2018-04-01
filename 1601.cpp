#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
string s;
int a[505],b[505];
int main(){
	int n,m,i,j,t;
	cin>>s;
	n=s.size();
	for(i=0;i<n;i++){
		a[n-i]=s[i]-'0';
	}
	cin>>s;
	m=s.size();
	for(i=0;i<m;i++){
		b[m-i]=s[i]-'0';
	}
	t=max(n,m);
	for(i=1;i<=t;i++){
		b[i]+=a[i];
		if(b[i]>=10){
			b[i+1]++;
			b[i]%=10;
			if(i==t){
				t++;
			}
		}
	}
	for(i=t;i>=1;i--){
		cout<<b[i];
	}
	cout<<endl;
	return 0;
}

