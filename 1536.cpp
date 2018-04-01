#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int f[1005];
int up(int n);
void merge(int n,int m);
int main(){
    int n,m,a,b,i,ans;
    while(cin>>n>>m){
        ans=0;
        for(i=1;i<=n;i++){
            f[i]=i;
        }
        for(i=1;i<=m;i++){
            cin>>a>>b;
            merge(a,b);
        }
        for(i=1;i<=n;i++){
            ans+=(f[i]==i);
        }
        cout<<(ans-1)<<endl;
    }
}
int up(int n){
    if(f[n]==n){
        return n;
    }else{
        return f[n]=up(f[n]);
    }
}
void merge(int n,int m){
    int i=up(n),j=up(m);
    if(i!=j){
        f[j]=i;
    }
}
