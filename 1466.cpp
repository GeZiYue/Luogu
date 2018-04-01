#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
long long dp[400];
int main(){
    int n,m,sum,i,j;
    cin>>n;
    sum=n*(n+1)/2;
    if(sum&1){
        cout<<0<<endl;
        return 0;
    }
    m=sum/2;
    dp[0]=1;
    for(i=1;i<=n;i++){
        for(j=m;j>=i;j--){
            dp[j]+=dp[j-i];
        }
    }
    cout<<dp[m]/2<<endl;
    return 0;
}
