#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<queue>
using namespace std;
int xx[15]={0,-2,-2,-2,-2,-1,-1,1,1,2,2,2,2};
int yy[15]={0,-2,-1,1,2,-2,2,-2,2,-2,-1,1,2};
bool t[45][45];
class Point{
public:
	int x,y,sum;
	Point add(int i){
		Point ans;
		ans.x=x+xx[i];
		ans.y=y+yy[i];
		ans.sum=sum+1;
		return ans;
	}
	bool check(){
		if(t[x][y]==1){
			return 0;
		}else{
			t[x][y]=1;
		}
		if(x<1||y<1||x>40||y>40){
			return 0;
		}else{
			return 1;
		}
	}
};
istream& operator>>(istream &input,Point &i){
	input>>i.x>>i.y;
	return input;
}
queue<Point>a;
int main(){
	int i,n1,n2;
	Point now,k;
	cin>>now;
	now.sum=0;
	a.push(now);
	while(!a.empty()){
		now=a.front();
		if(now.x==1&&now.y==1){
			cout<<now.sum<<endl;
			break;
		}
		a.pop();
		for(i=1;i<=12;i++){
			k=now.add(i);
			if(k.check()){
				a.push(k);
			}
		}
	}
	memset(t,0,sizeof(t));
	while(!a.empty()){
		a.pop();
	}
	cin>>now;
	now.sum=0;
	a.push(now);
	while(!a.empty()){
		now=a.front();
		if(now.x==1&&now.y==1){
			cout<<now.sum<<endl;
			break;
		}
		a.pop();
		for(i=1;i<=12;i++){
			k=now.add(i);
			if(k.check()){
				a.push(k);
			}
		}
	}
	return 0;
}
