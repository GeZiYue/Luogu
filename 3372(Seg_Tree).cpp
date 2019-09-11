#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define ll unsigned long long int
#define lc(a) (a<<1)
#define rc(a) ((a<<1)+1)
struct Node{
    ll num;
    int tags;
}Tree[400005];
ll a[100005];
void build(int n,int L,int R);
void down(int n);
ll query(int n,int nL,int nR,int qL,int qR);
void update(int n,int nL,int nR,int uL,int uR,int num);
int main(){
    int n,m,i,b,c,d,e;
    cin>>n>>m;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    for(i=1;i<=m;i++){
        cin>>b;
        if(b==1){
            cin>>c>>d>>e;
            update(1,1,n,c,d,e);
        }else{
            cin>>c>>d;
            cout<<query(1,1,n,c,d)<<endl;
        }
    }
    return 0;
}
void build(int n,int L,int R){
    if(L==R){
        Tree[n].num=a[L];
        return;
    }else{
        int M=(L+R)>>1;
        build(lc(n),L,M);
        build(rc(n),M+1,R);
        Tree[n].num=Tree[lc(n)].num+Tree[rc(n)].num;
        return;
    }
}
void down(int n,int L,int R){
    Tree[lc(n)].tags+=Tree[n].tags;
    Tree[rc(n)].tags+=Tree[n].tags;
    int M=(L+R)>>1;
    Tree[lc(n)].num+=Tree[n].tags*(M-L+1);
    Tree[rc(n)].num+=Tree[n].tags*(R-M);
    Tree[n].tags=0;
}
ll query(int n,int nL,int nR,int qL,int qR){
    if(nL>=qL&&nR<=qR){
        return Tree[n].num;
    }
    if(nR<qL||nL>qR){
        return 0;
    }
    down(n,nL,nR);
    int M=(nL+nR)>>1;
    return query(lc(n),nL,M,qL,qR)+query(rc(n),M+1,nR,qL,qR);
}
void update(int n,int nL,int nR,int uL,int uR,int num){
    if(nL>=uL&&nR<=uR){
        Tree[n].tags+=num;
        Tree[n].num+=num*(nR-nL+1);
        return;
    }
    if(nR<uL||nL>uR){
        return;
    }
    down(n,nL,nR);
    int M=(nL+nR)>>1;
    update(lc(n),nL,M,uL,uR,num);
    update(rc(n),M+1,nR,uL,uR,num);
    Tree[n].num=Tree[lc(n)].num+Tree[rc(n)].num;
}