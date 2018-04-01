#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define lc(a) (a<<1)
#define rc(a) (lc(a)|1)
#define oo 2147483647
int Tree[400005];
int a[100005];
void build(int n,int L,int R);
int query(int n,int nL,int nR,int uL,int uR);
int main(){
	int n,m,i,x,y;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	for(i=1;i<=m;i++){
		cin>>x>>y;
		cout<<query(1,1,n,x,y)<<' ';
	}
	cout<<endl;
	return 0;
}
void build(int n,int L,int R){
	if(L==R){
		Tree[n]=a[L];
	}else{
		int M=(L+R)>>1;
		build(lc(n),L,M);
		build(rc(n),M+1,R);
		Tree[n]=min(Tree[lc(n)],Tree[rc(n)]);
	}
}
int query(int n,int nL,int nR,int uL,int uR){
	if(nL>=uL&&nR<=uR){
		return Tree[n];
	}
	if(nR<uL||nL>uR){
		return oo;
	}
	int M=(nL+nR)>>1;
	return min(query(lc(n),nL,M,uL,uR),query(rc(n),M+1,nR,uL,uR));
}
