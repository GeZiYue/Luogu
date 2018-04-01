#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
pair<int,int>x[1005],y[1005],ansx[1005],ansy[1005];
int xx,yy;
bool cmp1(pair<int,int> i,pair<int,int> j){
	return i.first>j.first;
}
bool cmp2(pair<int,int> i,pair<int,int> j){
	return i.second<j.second;
}
int main(){
	int n,m,k,l,s,i,l1,l2,l3,l4;
	cin>>n>>m>>k>>l>>s;
	for(i=1;i<=n;i++){
		x[i].second=i;
	}
	for(i=1;i<=m;i++){
		y[i].second=i;
	}
	for(i=1;i<=s;i++){
		cin>>l1>>l2>>l3>>l4;
		if(l1==l3){
			y[min(l2,l4)].first++;
		}else{
			x[min(l1,l3)].first++;
		}
	}
	sort(x+1,x+n,cmp1);
	sort(y+1,y+m,cmp1);
	for(i=1;i<=k;i++){
		ansx[i]=x[i];
	}
	for(i=1;i<=l;i++){
		ansy[i]=y[i];
	}
	sort(ansx+1,ansx+k+1,cmp2);
	sort(ansy+1,ansy+l+1,cmp2);
	for(i=1;i<=k;i++){
		cout<<ansx[i].second<<' ';
	}
	cout<<endl;
	for(i=1;i<=l;i++){
		cout<<ansy[i].second<<' ';
	}
	cout<<endl;
	return 0;
}
