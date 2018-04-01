#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
class Node{
public:
	int x,y;
	bool operator<=(Node&);
}a[5005];
bool Node::operator<=(Node&i){
	if(this->x==i.x){
		return (this->y)<(i.y);
	}else{
		return (this->x)<(i.x);
	}
}
bool cmp(Node i,Node j){
	return i<=j;
}
int dp[5005];
int main(){
	int n,i,j,ans=1;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	dp[1]=1;
	for(i=2;i<=n;i++){
		dp[i]=1;
		for(j=1;j<i;j++){
			if(a[i].y>=a[j].y){
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
		ans=max(ans,dp[i]);
	}
	cout<<ans<<endl;
	return 0;
}

