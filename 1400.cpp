#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Mod 1000000009
typedef unsigned long long int ll;
int a[600005];
int main(){
    int n,m,l=1,i;
    ll ans=1;
    cin>>n>>m;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(i=2;i<=n;i++){
        while(a[l]<(a[i]-m)&&i>l){
            l++;
        }
        ans*=i-l+1;
        ans%=Mod;
    }
    cout<<ans<<endl;
}
