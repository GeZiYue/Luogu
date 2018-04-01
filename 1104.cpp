#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
struct Node{
	int y,m,d,id;
	string s;
}a[105];
bool cmp(Node i,Node j);
int main(){
	int n,i;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i].s>>a[i].y>>a[i].m>>a[i].d;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++){
		cout<<a[i].s<<endl;
	}
	return 0;
}
bool cmp(Node i,Node j){
	if(i.y==j.y){
		if(i.m==j.m){
			if(i.d==j.d){
				return i.id>j.id;
			}else{
				return i.d<j.d;
			}
		}else{
			return i.m<j.m;
		}
	}else{
		return i.y<j.y;
	}
}

