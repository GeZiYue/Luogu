#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
struct Node{
	int x1,x2;
	int y1,y2;
}a[10005];
int main(){
	int n,x,y,i,j,l,ans=-1;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i].x1>>a[i].y1;
		cin>>l;
		a[i].x2=a[i].x1+l;
		cin>>l;
		a[i].y2=a[i].y1+l;
	}
	cin>>x>>y;
	for(i=n;i>=1;i--){
		if(x>=a[i].x1&&x<=a[i].x2&&y>=a[i].y1&&y<=a[i].y2){
			ans=i;
			break;
		}
	}
	cout<<ans<<endl;
	return 0;
}

