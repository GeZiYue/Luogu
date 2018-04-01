#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int m,n,i,a,maxi=0,mini=0;
    cin>>m>>n;
    for(i=1;i<=n;i++){
        cin>>a;
        maxi=max(maxi,max(m-a+1,a));
        mini=max(mini,min(m-a+1,a));
    }
    cout<<mini<<" "<<maxi;
	return 0;
}

