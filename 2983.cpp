#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define ll unsigned long long int
struct Node{
    ll num;
    ll sum;
}a[100005];
bool cmp(Node a,Node b);
int main(){
    ll n,m,i,ans=0;
    cin>>n>>m;
    for(i=1;i<=n;i++){
        cin>>a[i].sum>>a[i].num;
    }
    sort(a+1,a+n+1,cmp);
    for(i=1;i<=n;i++){
        if(a[i].sum*a[i].num<m){
            ans+=a[i].num;
            m-=a[i].sum*a[i].num;
        }else{
            ans+=(m/a[i].sum);
            break;
        }
    }
    cout<<ans<<endl;
}
bool cmp(Node a,Node b){
    return a.sum<b.sum;
}