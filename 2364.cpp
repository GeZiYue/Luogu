#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
struct Node{
	int num;
	string ans;
}dp[105][105][105];
Node cmp(Node i,Node j){
	if(i.num>j.num){
		return i;
	}else{
		return j;
	}
}
int main(){
	int n,m,k,i,j,l;
	char a[105],b[105],c[105];
	cin>>a+1>>b+1>>c+1;
	n=strlen(a+1);
	m=strlen(b+1);
	k=strlen(c+1);
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			for(l=1;l<=k;l++){
				if(a[i]==b[j]&&b[j]==c[l]){
					dp[i][j][l].num=dp[i-1][j-1][l-1].num+1;
					dp[i][j][l].ans=dp[i-1][j-1][l-1].ans+a[i];
				}else{
					dp[i][j][l]=cmp(dp[i-1][j][l],cmp(dp[i][j-1][l],cmp(dp[i][j][l-1],cmp(dp[i-1][j-1][l],cmp(dp[i-1][j][l-1],cmp(dp[i][j-1][l-1],dp[i-1][j-1][l-1]))))));
				}
			}
		}
	}
	cout<<dp[n][m][k].ans<<endl;
	return 0;
}

