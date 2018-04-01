#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
typedef unsigned long long int ll;
class Time{
public:
	int h,m,s;
	void Get();
	ll Change();
	Time operator-(Time i);
};
int main(){
	Time a,b,c;
	ll k;
	a.Get();
	b.Get();
	cin>>k;
	c=b-a;
	cout<<k*c.Change()<<endl;
	return 0;
}
void Time::Get(){
	char c;
	cin>>this->h>>c>>this->m>>c>>this->s;
}
ll Time::Change(){
	ll ans;
	ans=this->h*3600+this->m*60+this->s;
	return ans;
}
Time Time::operator-(Time i){
	Time ans;
	ans.h=this->h-i.h;
	ans.m=this->m-i.m;
	ans.s=this->s-i.s;
	if(ans.s<0){
		ans.s+=60;
		ans.m--;
	}
	if(ans.m<0){
		ans.m+=60;
		ans.h--;
	}
	return ans;
}

