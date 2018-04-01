#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
#include<queue>
using namespace std;
struct P{
	int x;
	int y;
	int sum;
};
bool operator==(const P&i,const P&j){
	if(i.x==j.x&&i.y==j.y){
		return true;
	}else{
		return false;
	}
}
queue<P>a;
char s[2005][2005];
bool t[2005][2005];
int xx[5]={0,1,0,-1,0};
int yy[5]={0,0,1,0,-1};
int main(){
	P now,ans,k;
	int n,m,i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>s[i][j];
			if(s[i][j]=='m'){
				now.x=i;
				now.y=j;
				now.sum=0;
				a.push(now);
				t[i][j]=1;
			}
			if(s[i][j]=='d'){
				ans.x=i;
				ans.y=j;
			}
			if(s[i][j]=='#'){
				t[i][j]=1;
			}
		}
	}
	while(!a.empty()){
		now=a.front();
		if(now==ans){
			cout<<now.sum<<endl;
			return 0;
		}
		a.pop();
		for(i=1;i<=4;i++){
			k.x=now.x+xx[i];
			k.y=now.y+yy[i];
			k.sum=now.sum+1;
			if(k.x>=1&&k.x<=n&&k.y>=1&&k.y<=m&&t[k.x][k.y]==0){
				a.push(k);
				t[k.x][k.y]=1;
			}
		}
	}
	cout<<"No Way!"<<endl;
	return 0;
}

