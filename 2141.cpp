#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<map>
using namespace std;
map<int,bool>t;
int a[105];
int main(){
    int n,i,j,k,ans=0;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    for(i=1;i<n;i++){
        for(j=i+1;j<=n;j++){
            t[a[i]+a[j]]=1;
        }
    }
    for(i=1;i<=n;i++){
        ans+=t[a[i]];
    }
    cout<<ans<<endl;
}
