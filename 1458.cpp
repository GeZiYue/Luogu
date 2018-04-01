#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
int gcd(int a,int b);
bool check(int a,int b);
class Node{
public:
	void Print(){
		cout<<a<<'/'<<b<<endl;
	}
	double Return(){
		return ab;
	}
	void Get(int i,int j){
		a=i;
		b=j;
		ab=a*1.0/b;
	}
private:
	int a,b;
	double ab;
}f[30005];
bool cmp(Node i,Node j){
	return i.Return()<j.Return();
}
int main(){
	int n,m=0,i,j;
	cin>>n;
	cout<<0<<'/'<<1<<endl;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(check(i,j)&&i*1.0/j<=1){
				f[++m].Get(i,j);
			}
		}
	}
	sort(f+1,f+m+1,cmp);
	for(i=1;i<=m;i++){
		f[i].Print();
	}
	return 0;
}
int gcd(int a,int b){
	if(b==0){
		return a;
	}else{
		return gcd(b,a%b);
	}
}
bool check(int a,int b){
	if(gcd(a,b)==1){
		return true;
	}else{
		return false;
	}
}

