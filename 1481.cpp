#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
string a[2005];
int dp[2005];
bool operator<(string &i,string &j);
int main(){
    int n,i,j,ans=0;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    for(i=1;i<=n;i++){
        dp[i]=1;
        for(j=1;j<i;j++){
            if(a[j]<a[i]){
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
}
bool operator<(string &i,string &j){
    int n=i.size(),m=j.size(),k;
    if(n>m){
        return false;
    }
    for(k=0;k<n;k++){
        if(i[k]!=j[k]){
            return false;
        }
    }
    return true;
}
