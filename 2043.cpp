#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
int a[10005];
int main(){
	int n,i,j,now,flag;
	cin>>n;
	flag=n-1;
	for(i=1;i<=n;i++){
		a[i]=i;
	}
	for(i=2;flag>0;i++){
		now=0;
		for(j=1;j<=n;j++){
			while(a[j]%i==0){
				a[j]/=i;
				now++;
				if(a[j]==1){
					flag--;
				}
			}
		}
		if(now!=0){
			cout<<i<<' '<<now<<endl;
		}
	}
	return 0;
}

