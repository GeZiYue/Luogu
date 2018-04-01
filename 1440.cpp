#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<queue>
using namespace std;
class Num{
public:
	int x,s;
	friend bool operator<(Num i,Num j){
		return i.s>j.s;
	}
};
priority_queue<Num>a;
int main(){
	int n,m,now,i;
	Num k;
	cin>>n>>m;
	cout<<0<<endl;
	cin>>k.s;
	k.x=1;
	a.push(k);
	for(i=2;i<=n;i++){
		scanf("%d",&k.s);
		k.x=i;
		now=max(1,i-m);
		while(a.top().x<now){
			a.pop();
		}
		printf("%d\n",a.top().s);
		a.push(k);
	}
	return 0;
}

