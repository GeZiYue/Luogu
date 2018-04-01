#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define ll long long int
#define ls(a) (a<<1)
#define rs(a) (ls(a)+1)
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
struct Node{
    ll num;
    ll tag1;
    ll tag2;
}Tree[400005];
ll a[100005];
ll Mod;
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void build(ll n,ll L,ll R);
void down(ll n,ll L,ll R);
ll query(ll n,ll nL,ll nR,ll qL,ll qR);
void updatemult(ll n,ll nL,ll nR,ll uL,ll uR,ll num);
void updateadd(ll n,ll nL,ll nR,ll uL,ll uR,ll num);
int main(){
    ll n,m,i,b,c,d,e;
    read(n);
    read(Mod);
    for(i=1;i<=n;i++){
        read(a[i]);
    }
    build(1,1,n);
    read(m);
    for(i=1;i<=m;i++){
        read(b);
        if(b==1){
            read(c);
            read(d);
            read(e);
            updatemult(1,1,n,c,d,e);
        }else{
            if(b==2){
                read(c);
                read(d);
                read(e);
                updateadd(1,1,n,c,d,e);
            }else{
                read(c);
                read(d);
                write(query(1,1,n,c,d));
                EL;
            }
        }
    }
}
template<class T1>void read(T1 &r_e_a_d){
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while(!isNum(ch)){
        if(ch=='-'){
            flag=-1;
        }
        ch=getchar();
    }
    while(isNum(ch)){
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d=flag*k;
}
template<class T1>void write(T1 w_r_i_t_e){
    if(w_r_i_t_e<0){
        putchar('-');
        write(-w_r_i_t_e);
    }else{
        if(w_r_i_t_e<10){
            putchar(w_r_i_t_e+'0');
        }else{
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
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
        build(ls(n),L,M);
        build(rs(n),M+1,R);
        Tree[n].num=(Tree[ls(n)].num+Tree[rs(n)].num)%Mod;
    }
}
void down(ll n,ll L,ll R){
    ll M=(L+R)>>1;
    Tree[ls(n)].num=(Tree[ls(n)].num*Tree[n].tag1+Tree[n].tag2*(M-L+1))%Mod;
    Tree[rs(n)].num=(Tree[rs(n)].num*Tree[n].tag1+Tree[n].tag2*(R-M))%Mod;
    Tree[ls(n)].tag1=Tree[ls(n)].tag1*Tree[n].tag1%Mod;
    Tree[rs(n)].tag1=Tree[rs(n)].tag1*Tree[n].tag1%Mod;
    Tree[ls(n)].tag2=(Tree[ls(n)].tag2*Tree[n].tag1%Mod+Tree[n].tag2)%Mod;
    Tree[rs(n)].tag2=(Tree[rs(n)].tag2*Tree[n].tag1%Mod+Tree[n].tag2)%Mod;
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
    return (query(ls(n),nL,M,qL,qR)+query(rs(n),M+1,nR,qL,qR))%Mod;
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
    updatemult(ls(n),nL,M,uL,uR,num);
    updatemult(rs(n),M+1,nR,uL,uR,num);
    Tree[n].num=(Tree[ls(n)].num+Tree[rs(n)].num)%Mod;
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
    updateadd(ls(n),nL,M,uL,uR,num);
    updateadd(rs(n),M+1,nR,uL,uR,num);
    Tree[n].num=(Tree[ls(n)].num+Tree[rs(n)].num)%Mod;
}
