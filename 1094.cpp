#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int a[30005];
int main(){
    int n,m,i,j,ans;
    cin>>m>>n;
    ans=n;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    for(i=1,j=n;i<j;j--){
        if(a[i]+a[j]<=m){
            i++;
            ans--;
        }
    }
    cout<<ans<<endl;
}
