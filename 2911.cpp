#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int t[105];
int main(){
	int a,b,c,i,j,k,maxi=0,ans;
	cin>>a>>b>>c;
	for(i=1;i<=a;i++){
		for(j=1;j<=b;j++){
			for(k=1;k<=c;k++){
				t[i+j+k]++;
			}
		}
	}
	for(i=1;i<=a+b+c;i++){
		if(t[i]>maxi){
			maxi=t[i];
			ans=i;
		}
	}
	cout<<ans<<endl;
	return 0;
}

