#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef unsigned long long int ll;
ll gcd(ll a,ll b);
int main(){
    int t,n,i,ans,a;
    cin>>t;
    while(t--){
        cin>>n;
        cin>>a>>ans;
        ans/=gcd(a,ans);
        for(i=3;i<=n;i++){
            cin>>a;
            ans/=gcd(a,ans);
        }
        if(ans==1){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }
}
ll gcd(ll a,ll b){
    if(b==0){
        return a;
    }else{
        return gcd(b,a%b);
    }
}