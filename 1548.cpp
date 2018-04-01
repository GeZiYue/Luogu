#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
typedef unsigned long long int ll;
int main(){
    int n,m,i;
    ll ans1=0,ans2=0;
    cin>>n>>m;
    for(i=1;i<=min(n,m);i++){
        ans1+=(n-i+1)*(m-i+1);
    }
    ans2=(n*(n+1)/2)*(m*(m+1)/2);
    ans2-=ans1;
    cout<<ans1<<' '<<ans2<<endl;
}
