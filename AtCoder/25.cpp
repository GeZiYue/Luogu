#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int main(){
    int n,m,i,j,ans=0,now,a;
    cin>>n>>m;
    for(i=1;i<=n;i++){
        now=0;
        for(j=1;j<=m;j++){
            cin>>a;
            now+=a;
        }
        ans=max(ans,now);
    }
    cout<<ans<<endl;
    return 0;
}
