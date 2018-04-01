#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int a[10005],b[1005];
int main(){
    int n,m,i,j,mini,ans=0,k,t,maxi=0;
    cin>>n>>m;
    k=0;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    while(k<n){
        mini=2147483647;
        for(i=1;i<=m;i++){
            if(b[i]!=0){
                mini=min(mini,b[i]);
            }
        }
        if(mini==2147483647){
            mini=0;
        }
        for(i=1;i<=m;i++){
            b[i]-=mini;
            if(b[i]==0){
                if(k==n){
                    ;
                }else{
                    b[i]=a[++k];
                }
            }
        }
        ans+=mini;
    }
    for(i=1;i<=m;i++){
        maxi=max(maxi,b[i]);
    }
    ans+=maxi;
    cout<<ans<<endl;
    return 0;
}
