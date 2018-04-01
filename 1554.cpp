#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int t[10];
int main(){
	int l,r,i,j;
	cin>>l>>r;
	for(i=l;i<=r;i++){
		j=i;
		while(j){
			t[j%10]++;
			j/=10;
		}
	}
	for(i=0;i<=9;i++){
		cout<<t[i]<<' ';
	}
	return 0;
}

