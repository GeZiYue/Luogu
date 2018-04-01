#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int a[3005],dp1[3005][3005],dp2[3005][3005];
int main(){
	int n=0,m,l,i,j,maxi=0,mini=100000005,t1,t2;
	cin>>l>>m;
	for(i=1;i<=l;i++){
		cin>>a[++n];
		if(a[n]>119){
			n--;
		}
	}
	if(n<m){
		cout<<"You can't do it."<<endl;
	}
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			dp1[i][j]=dp2[i][j]=100000005;
		}
	}
	dp1[0][0]=dp2[0][0]=0;
	for(i=1;i<=n;i++){
		for(j=1;j<=i;j++){
			t1=dp1[i-1][j-1];
			t2=dp2[i-1][j-1]+a[i];
			if(t2>119){
				t1++;
				t2=a[i];
			}
			if(t1<dp1[i-1][j]){
				dp1[i][j]=t1;
				dp2[i][j]=t2;
			}else{
				if(t1==dp1[i-1][j]){
					dp1[i][j]=t1;
					dp2[i][j]=min(dp2[i-1][j],t2);
				}else{
					dp1[i][j]=dp1[i-1][j];
					dp2[i][j]=dp2[i-1][j];
				}
			}
			if(j>=m){
				mini=min(mini,dp1[i][j]+(dp2[i][j]!=0));
			}
		}
	}
	cout<<mini<<endl;
	return 0;
}

