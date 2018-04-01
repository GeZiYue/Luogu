#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define ll long long int
#define N 100005
#define lc(n) (n<<1)
#define rc(n) ((n<<1)|1)
#define gswap(n,m) (n^=m^=n^=m)
ll n,Mod;
ll sum[4*N],tag[4*N];
ll hed[2*N],nxt[2*N],to[2*N];
ll dep[N],go[N],back[N],siz[N],son[N],fa[N],top[N];
ll id1,id2;
ll value[N];
bool isnum(char ch);
template<class T1>
    void read(T1& readnumber);
void add(ll x,ll y);
void dfs1(ll x);
void dfs2(ll x);
void Way_update(ll x,ll y,ll num);
ll Way_query(ll x,ll y);
void Subtree_update(ll x,ll num);
ll Subtree_query(ll x);
void On_Tree_build(ll n,ll nL,ll nR);
void On_Tree_down(ll n,ll nL,ll nR);
void On_Tree_update(ll n,ll nL,ll nR,ll uL,ll uR,ll num);
ll On_Tree_query(ll n,ll nL,ll nR,ll qL,ll qR);
int main(){
    ll m,root,i;
    ll l1,l2,l3,l4;
    read(n);
    read(m);
    read(root);
    read(Mod);
    for(i=1;i<=n;i++){
        read(value[i]);
    }
    for(i=1;i<n;i++){
        read(l1);
        read(l2);
        add(l1,l2);
        add(l2,l1);
    }
    dep[root]=1;
    dfs1(root);
    top[root]=root;
    dfs2(root);
    On_Tree_build(1,1,n);
    for(i=1;i<=m;i++){
        read(l1);
        if(l1==1){
            read(l2);
            read(l3);
            read(l4);
            l4%=Mod;
            Way_update(l2,l3,l4);
        }else{
            if(l1==2){
                read(l2);
                read(l3);
                printf("%lld\n",Way_query(l2,l3));
            }else{
                if(l1==3){
                    read(l2);
                    read(l3);
                    l3%=Mod;
                    Subtree_update(l2,l3);
                }else{
                    read(l2);
                    printf("%lld\n",Subtree_query(l2));
                }
            }
        }
    }
    return 0;
}
bool isnum(char ch){
    return (ch>='0'&&ch<='9');
}
template<class T1>
    void read(T1& readnumber){
        T1 k=0;
        bool flag=0;
        char ch;
        while(!isnum(ch=getchar())){
            if(ch=='-'){
                flag=1;
            }
        }
        k=ch-'0';
        while(isnum(ch=getchar())){
            k=(k<<1)+(k<<3)+ch-'0';
        }
        if(flag){
            readnumber=-k;
        }else{
            readnumber=k;
        }
    }
void add(ll x,ll y){
    nxt[++id1]=hed[x];
    hed[x]=id1;
    to[id1]=y;
}
void dfs1(ll x){
    siz[x]=1;
    son[x]=0;
    for(ll i=hed[x];i;i=nxt[i]){
        if(to[i]!=fa[x]){
            fa[to[i]]=x;
            dep[to[i]]=dep[x]+1;
            dfs1(to[i]);
            siz[x]+=siz[to[i]];
            if(son[x]==0||siz[to[i]]>siz[son[x]]){
                son[x]=to[i];
            }
        }
    }
}
void dfs2(ll x){
    go[x]=++id2;
    back[id2]=value[x]%Mod;
    if(son[x]){
        top[son[x]]=top[x];
        dfs2(son[x]);
    }
    for(ll i=hed[x];i;i=nxt[i]){
        if(to[i]!=son[x]&&to[i]!=fa[x]){
            top[to[i]]=to[i];
            dfs2(to[i]);
        }
    }
}
void Way_update(ll x,ll y,ll num){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            gswap(x,y);
        }
        On_Tree_update(1,1,n,go[top[x]],go[x],num);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]){
         gswap(x,y);
    }
    On_Tree_update(1,1,n,go[x],go[y],num);
}
ll Way_query(ll x,ll y){
    ll Ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            gswap(x,y);
        }
        Ans=(Ans+On_Tree_query(1,1,n,go[top[x]],go[x])%Mod)%Mod;
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]){
         gswap(x,y);
    }
    Ans=(Ans+On_Tree_query(1,1,n,go[x],go[y])%Mod)%Mod;
    return Ans;
}
void Subtree_update(ll x,ll num){
    On_Tree_update(1,1,n,go[x],go[x]+siz[x]-1,num);
}
ll Subtree_query(ll x){
    return On_Tree_query(1,1,n,go[x],go[x]+siz[x]-1);
}
void On_Tree_build(ll n,ll nL,ll nR){
    if(nL==nR){
        sum[n]=back[nL]%Mod;
    }else{
        ll M=(nL+nR)>>1;
        On_Tree_build(lc(n),nL,M);
        On_Tree_build(rc(n),M+1,nR);
        sum[n]=(sum[lc(n)]+sum[rc(n)])%Mod;
    }
}
void On_Tree_down(ll n,ll nL,ll nR){
    ll M=(nL+nR)>>1;
    sum[lc(n)]=(sum[lc(n)]%Mod+tag[n]%Mod*((M-nL+1)%Mod))%Mod;
    sum[rc(n)]=(sum[rc(n)]%Mod+tag[n]%Mod*((nR-M)%Mod))%Mod;
    tag[lc(n)]=(tag[lc(n)]%Mod+tag[n]%Mod)%Mod;
    tag[rc(n)]=(tag[rc(n)]%Mod+tag[n]%Mod)%Mod;
    tag[n]=0;
}
void On_Tree_update(ll n,ll nL,ll nR,ll uL,ll uR,ll num){
    if(nL>=uL&&nR<=uR){
        sum[n]=(sum[n]+(nR-nL+1)*num%Mod)%Mod;
        tag[n]=(tag[n]+num%Mod)%Mod;
        return;
    }
    if(nR<uL||nL>uR){
        return;
    }
    On_Tree_down(n,nL,nR);
    ll M=(nL+nR)>>1;
    On_Tree_update(lc(n),nL,M,uL,uR,num);
    On_Tree_update(rc(n),M+1,nR,uL,uR,num);
    sum[n]=(sum[lc(n)]%Mod+sum[rc(n)]%Mod)%Mod;
}
ll On_Tree_query(ll n,ll nL,ll nR,ll qL,ll qR){
    if(nL>=qL&&nR<=qR){
        return sum[n]%Mod;
    }
    if(nR<qL||nL>qR){
        return 0;
    }
    On_Tree_down(n,nL,nR);
    ll M=(nL+nR)>>1;
    return (On_Tree_query(lc(n),nL,M,qL,qR)%Mod+On_Tree_query(rc(n),M+1,nR,qL,qR)%Mod)%Mod;
}
