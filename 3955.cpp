#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int a[1005];
int pow(int t);
int main(){
    int x,y,i,j,n,m,t;
    cin>>n>>m;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    for(i=1;i<=m;i++){
        cin>>x>>y;
        t=pow(x);
        for(j=1;j<=n;j++){
            if(a[j]%t==y){
                cout<<a[j]<<endl;
                break;
            }
        }
        if(j>n){
            cout<<-1<<endl;
        }
    }
}
int pow(int t){
    int i,ans=1;
    for(i=1;i<=t;i++){
        ans*=10;
    }
    return ans;
}
