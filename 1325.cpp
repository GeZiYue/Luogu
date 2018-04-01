#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iomanip>
using namespace std;
typedef long long ll;
struct Node{
	int x,y,a,b;
}num[100005];
bool cmp(Node a,Node b){
	if(a.b!=b.b)return a.b<b.b;
	return a.a<a.a;
}
int main(){
    int n,d,i,now,s=1;
    cin>>n>>d;
    for(i=1;i<=n;i++){
    	cin>>num[i].x>>num[i].y;
    	if(num[i].y>d){
    		cout<<"-1"<<endl;
    		return 0;
    	}
    	num[i].a=num[i].x-sqrt((double)(d*d-num[i].y*num[i].y));
    	num[i].b=num[i].x+sqrt((double)(d*d-num[i].y*num[i].y));
    }
    sort(num+1,num+n+1,cmp);
    now=num[1].b;
    for(i=2;i<=n;i++){
    	if(num[i].a>now){
    		now=num[i].b;
    		s++;
    	}
    }
    cout<<s;
	return 0;
}

