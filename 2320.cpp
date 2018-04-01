#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int ans[100005];
int main(){
    int sum=0,n,i;
    cin>>n;
    while(n){
        ans[++sum]=(n&1?(n+1)>>1:n>>1);
        n>>=1;
    }
    cout<<sum<<endl;
    for(i=sum;i>=1;i--){
        cout<<ans[i]<<' ';
    }
    cout<<endl;
}
