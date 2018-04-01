#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
using namespace std;
bool t[30005];
int main(){
	int n,m,i,j,maxi=0;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>j;
		maxi=max(maxi,j);
		t[j]=1;
	}
	for(i=1,j=0;i<=maxi;i++){
		if(t[i]){
			j++;
		}
		if(j==m){
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<"NO RESULT"<<endl;
	return 0;
}

