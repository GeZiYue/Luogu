#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef unsigned long long int ll;
int a[30];
ll dp[10005];
int main(){
    int n,m,i,j;
    cin>>n>>m;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    dp[0]=1;
    for(i=1;i<=n;i++){
        for(j=a[i];j<=m;j++){
            dp[j]+=dp[j-a[i]];
        }
    }
    cout<<dp[m]<<endl;
}
