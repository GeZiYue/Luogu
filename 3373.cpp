#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define ll long long int
#define lc(a) (a<<1)
#define rc(a) (lc(a)+1)
struct Node{
    ll num;
    ll tag1;
    ll tag2;
}Tree[400005];
ll a[100005];
ll Mod;
void build(ll n,ll L,ll R);
void down(ll n,ll L,ll R);
ll query(ll n,ll nL,ll nR,ll qL,ll qR);
void updatemult(ll n,ll nL,ll nR,ll uL,ll uR,ll num);
void updateadd(ll n,ll nL,ll nR,ll uL,ll uR,ll num);
int main(){
    ll n,m,i,b,c,d,e;
    cin>>n>>m>>Mod;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    for(i=1;i<=m;i++){
        cin>>b;
        if(b==1){
            cin>>c>>d>>e;
            updatemult(1,1,n,c,d,e);
        }else{
            if(b==2){
                cin>>c>>d>>e;
                updateadd(1,1,n,c,d,e);
            }else{
                cin>>c>>d;
                cout<<query(1,1,n,c,d)<<endl;
            }
        }
    }
}
void build(ll n,ll L,ll R){
    Tree[n].tag1=1;
    Tree[n].tag2=0;
    if(L==R){
        Tree[n].num=a[L]%Mod;
    }else{
        ll M=(L+R)>>1;
        build(lc(n),L,M);
        build(rc(n),M+1,R);
        Tree[n].num=(Tree[lc(n)].num+Tree[rc(n)].num)%Mod;
    }
}
void down(ll n,ll L,ll R){
    ll M=(L+R)>>1;
    Tree[lc(n)].num=(Tree[lc(n)].num*Tree[n].tag1+Tree[n].tag2*(M-L+1))%Mod;
    Tree[rc(n)].num=(Tree[rc(n)].num*Tree[n].tag1+Tree[n].tag2*(R-M))%Mod;
    Tree[lc(n)].tag1=Tree[lc(n)].tag1*Tree[n].tag1%Mod;
    Tree[rc(n)].tag1=Tree[rc(n)].tag1*Tree[n].tag1%Mod;
    Tree[lc(n)].tag2=(Tree[lc(n)].tag2*Tree[n].tag1%Mod+Tree[n].tag2)%Mod;
    Tree[rc(n)].tag2=(Tree[rc(n)].tag2*Tree[n].tag1%Mod+Tree[n].tag2)%Mod;
    Tree[n].tag1=1;
    Tree[n].tag2=0;
}
ll query(ll n,ll nL,ll nR,ll qL,ll qR){
    if(nL>=qL&&nR<=qR){
        return Tree[n].num%Mod;
    }
    if(nR<qL||nL>qR){
        return 0;
    }
    down(n,nL,nR);
    ll M=(nL+nR)>>1;
    return (query(lc(n),nL,M,qL,qR)+query(rc(n),M+1,nR,qL,qR))%Mod;
}
void updatemult(ll n,ll nL,ll nR,ll uL,ll uR,ll num){
    if(nL>=uL&&nR<=uR){
        Tree[n].tag1=Tree[n].tag1*num%Mod;
        Tree[n].tag2=Tree[n].tag2*num%Mod;
        Tree[n].num=Tree[n].num*num%Mod;
        return;
    }
    if(nR<uL||nL>uR){
        return;
    }
    down(n,nL,nR);
    ll M=(nL+nR)>>1;
    updatemult(lc(n),nL,M,uL,uR,num);
    updatemult(rc(n),M+1,nR,uL,uR,num);
    Tree[n].num=(Tree[lc(n)].num+Tree[rc(n)].num)%Mod;
}
void updateadd(ll n,ll nL,ll nR,ll uL,ll uR,ll num){
    if(nL>=uL&&nR<=uR){
        Tree[n].tag2=(Tree[n].tag2+num)%Mod;
        Tree[n].num=(Tree[n].num+num*(nR-nL+1))%Mod;
        return;
    }
    if(nR<uL||nL>uR){
        return;
    }
    down(n,nL,nR);
    ll M=(nL+nR)>>1;
    updateadd(lc(n),nL,M,uL,uR,num);
    updateadd(rc(n),M+1,nR,uL,uR,num);
    Tree[n].num=(Tree[lc(n)].num+Tree[rc(n)].num)%Mod;
}
