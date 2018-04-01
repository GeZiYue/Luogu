#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int x[40005];
int t[15005];
int ans[5][15005];
int main(){
	int n,m,i,a,b,c,d,l;
	cin>>n>>m;
	for(i=1;i<=m;i++){
		cin>>x[i];
		t[x[i]]++;
	}
	for(i=1;i*9<=n;i++){
		l=0;
		d=n;
		c=n-i;
		for(a=n-9*i-1;a>=1;a--){
			b=a+2*i;
			l+=t[d]*t[c];
			c--,d--;
			ans[1][a]+=l*t[b];
			ans[2][b]+=l*t[a];
		}
		l=0;
		a=1;
		b=1+2*i;
		for(d=9*i+2;d<=n;d++){
			c=d-i;
			l+=t[a]*t[b];
			a++,b++;
			ans[3][c]+=l*t[d];
			ans[4][d]+=l*t[c];
		}
	}
	for(i=1;i<=m;i++){
		cout<<ans[1][x[i]]<<' '<<ans[2][x[i]]<<' '<<ans[3][x[i]]<<' '<<ans[4][x[i]]<<endl;
	}
	return 0;
}

