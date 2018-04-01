#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int p[10005];
int up(int now);
void marge(int s1,int s2);
void check(int s1,int s2);
int main(){
	int n,m,a,t1,t2,i;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		p[i]=i;
	}
	for(i=1;i<=m;i++){
		cin>>a>>t1>>t2;
		if(a==1){
			marge(t1,t2);
		}else{
			check(t1,t2);
		}
	}
	return 0;
}
int up(int now){
	if(p[now]==now){
		return now;
	}else{
		return p[now]=up(p[now]);
	}
}
void marge(int s1,int s2){
	int p1=up(s1),p2=up(s2);
	if(p1==p2){
		return;
	}else{
		p[p2]=p1;
		return;
	}
}
void check(int s1,int s2){
	int p1=up(s1),p2=up(s2);
	if(p1==p2){
		cout<<'Y'<<endl;
	}else{
		cout<<'N'<<endl;
	}
}
