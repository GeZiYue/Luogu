#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
string name[1000005];
bool a[1000005];
#define abss(a) (a<0?-a:a)
int cha(int before,int f,int t,int k,int n);
int main(){
    int n,m,b,c,now=0,i;
    cin>>n>>m;
    for(i=0;i<n;i++){
        cin>>a[i]>>name[i];
    }
    for(i=1;i<=m;i++){
        cin>>b>>c;
        now=cha(now,a[now],b,c,n);
    }
    cout<<name[now]<<endl;
    return 0;
}
int cha(int before,int f,int t,int k,int n){
    int o,ans=before;
    if(f==t){
        o=-1;
    }else{
        o=1;
    }
    ans+=o*k;
    while(ans<0){
        ans+=n;
    }
    while(ans>=n){
        ans-=n;
    }
    return ans;
}