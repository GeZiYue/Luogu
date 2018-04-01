#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int a[55][55];
char c[505][505];
int xx1[10]={0,0,0,2,3,3,5,5};
int yy1[10]={0,0,4,6,0,4,2,6};
int xx2[10]={0,0,0,0,3,3,3,5,5,5};
int yy2[10]={0,1,2,3,1,2,3,3,4,5};
int xx3[10]={0,1,1,2,2,3,4};
int yy3[10]={0,0,4,0,4,6,6};
int xx4[10]={0,1,4,4};
int yy4[10]={0,5,1,5};
int xx5[15]={0,1,1,1,2,2,2,4,4,4,2,3};
int yy5[15]={0,1,2,3,1,2,3,2,3,4,5,5};
int main(){
	int n,m,x,y,xx,yy,i,j,k,l,maxx=0,maxy=0;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	memset(c,0,sizeof(c));
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			x=(n-i)*2+1;
			y=(n-i)*2+(j-1)*4+1;
			xx=x;
			yy=y;
			for(k=1;k<=a[i][j];k++){
				for(l=1;l<=7;l++){
					c[xx+xx1[l]][yy+yy1[l]]='+';
					maxx=max(maxx,xx+xx1[l]);
					maxy=max(maxy,yy+yy1[l]);
				}
				for(l=1;l<=9;l++){
					c[xx+xx2[l]][yy+yy2[l]]='-';
					maxx=max(maxx,xx+xx2[l]);
					maxy=max(maxy,yy+yy2[l]);
				}
				for(l=1;l<=6;l++){
					c[xx+xx3[l]][yy+yy3[l]]='|';
					maxx=max(maxx,xx+xx3[l]);
					maxy=max(maxy,yy+yy3[l]);
				}
				for(l=1;l<=3;l++){
					c[xx+xx4[l]][yy+yy4[l]]='/';
					maxx=max(maxx,xx+xx4[l]);
					maxy=max(maxy,yy+yy4[l]);
				}
				for(l=1;l<=11;l++){
					c[xx+xx5[l]][yy+yy5[l]]=' ';
					maxx=max(maxx,xx+xx5[l]);
					maxy=max(maxy,yy+yy5[l]);
				}
				xx+=3;
			}
		}
	}
	for(i=maxx;i>=1;i--){
		for(j=1;j<=maxy;j++){
			if(c[i][j]==0){
				cout<<'.';
			}else{
				cout<<c[i][j];
			}
		}
		cout<<endl;
	}
	return 0;
}
