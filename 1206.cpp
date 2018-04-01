#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Int(a) scanf("%d",&a)
int a[25],b[25];
int change(int n,int h,int s[]){
	int len=0;
	while(n){
		s[++len]=n%h;
		n/=h;
	}
	return len;
}
bool check(int len){
	int i;
	for(i=1;i*2<=len;i++){
		if(a[i]!=a[len-i+1]){
			return 0;
		}
	}
	return 1;
}
void print(int len,int s[]){
	int i;
	for(i=len;i>=1;i--){
		if(s[i]<10){
			cout<<s[i];
		}else{
			cout<<char('A'+s[i]-10);
		}
	}
}
int main(){
	int h,i,len1,len2;
	Int(h);
	for(i=1;i<=300;i++){
		len1=change(i*i,h,a);
		if(check(len1)){
			len2=change(i,h,b);
			print(len2,b);
			cout<<' ';
			print(len1,a);
			cout<<endl;
		}
	}
	return 0;
}
