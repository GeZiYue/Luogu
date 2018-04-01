#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int a[10005];
int main(){
	int n,i,j,ans=0;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	for(i=1;i<=n;i++){
		for(j=1;j<n;j++){
			if(a[j]>a[j+1]){
				ans++;
				swap(a[j],a[j+1]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

