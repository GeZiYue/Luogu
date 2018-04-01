#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int f[5005];
int up(int n);
void merge(int n,int m);
bool check(int n,int m);
int main(){
    int n,m,k,a,b,i;
    cin>>n>>m>>k;
    for(i=1;i<=n;i++){
        f[i]=i;
    }
    for(i=1;i<=m;i++){
        cin>>a>>b;
        merge(a,b);
    }
    for(i=1;i<=k;i++){
        cin>>a>>b;
        if(check(a,b)){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}
int up(int n){
    if(f[n]==n){
        return n;
    }else{
        return f[n]=up(f[n]);
    }
}
void merge(int n,int m){
    int x=up(n),y=up(m);
    if(x!=y){
        f[y]=f[x];
    }
}
bool check(int n,int m){
    return up(n)==up(m);
}