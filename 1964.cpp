#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;
int dp[30],w[150000];
map<string,int>a,b,c;
map<string,bool>d;
string s[105];
int main(){
	int n,m,l,i,j,k,maxi=0;
	cin>>m>>n;
	m=21-m;
	for(i=1;i<=n;i++){
		cin>>l>>j>>k;
		cin>>s[i];
		a[s[i]]+=l;
		b[s[i]]=j;
		c[s[i]]=k;
	}
	k=0;
	for(i=1;i<=n;i++){
		if(d[s[i]]==0){
			d[s[i]]=1;
			while(a[s[i]]>=c[s[i]]){
				w[++k]=c[s[i]]*b[s[i]];
				a[s[i]]-=c[s[i]];
			}
			if(a[s[i]]){
				w[++k]=a[s[i]]*b[s[i]];
			}
		}
	}
	for(i=1;i<=k;i++){
		for(j=m;j>=1;j--){
			dp[j]=max(dp[j],dp[j-1]+w[i]);
			maxi=max(maxi,dp[j]);
		}
	}
	cout<<maxi<<endl;
	return 0;
}

