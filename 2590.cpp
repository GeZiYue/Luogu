#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define ll long long int
#define N 30005
#define lc(n) (n<<1)
#define rc(n) ((n<<1)|1)
#define gswap(n,m) (n^=m^=n^=m)
ll n;
ll sum[4*N],maxn[4*N],tag[4*N];
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
ll Way_query_sum(ll x,ll y);
ll Way_query_max(ll x,ll y);
void On_Tree_build(ll n,ll nL,ll nR);
void On_Tree_down(ll n,ll nL,ll nR);
void On_Tree_update(ll n,ll nL,ll nR,ll uL,ll uR,ll num);
ll On_Tree_query_sum(ll n,ll nL,ll nR,ll qL,ll qR);
ll On_Tree_query_max(ll n,ll nL,ll nR,ll qL,ll qR);
int main(){
    ll m,i;
    ll l1,l2;
    char com[10];
    read(n);
    for(i=1;i<n;i++){
        read(l1);
        read(l2);
        add(l1,l2);
        add(l2,l1);
    }
    for(i=1;i<=n;i++){
        read(value[i]);
    }
    dep[1]=1;
    dfs1(1);
    top[1]=1;
    dfs2(1);
    On_Tree_build(1,1,n);
    read(m);
    for(i=1;i<=m;i++){
        cin>>com;
        read(l1);
        read(l2);
        if(strcmp(com,"CHANGE")==0){
            On_Tree_update(1,1,n,go[l1],go[l1],l2-On_Tree_query_sum(1,1,n,go[l1],go[l1]));
        }else{
            if(strcmp(com,"QSUM")==0){
                cout<<Way_query_sum(l1,l2)<<endl;
            }else{
                cout<<Way_query_max(l1,l2)<<endl;
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
    back[id2]=value[x];
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
ll Way_query_sum(ll x,ll y){
    ll Ans=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            gswap(x,y);
        }
        Ans=(Ans+On_Tree_query_sum(1,1,n,go[top[x]],go[x]));
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]){
         gswap(x,y);
    }
    Ans=(Ans+On_Tree_query_sum(1,1,n,go[x],go[y]));
    return Ans;
}
ll Way_query_max(ll x,ll y){
    ll Ans=-1000000000;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            gswap(x,y);
        }
        Ans=max(Ans,On_Tree_query_max(1,1,n,go[top[x]],go[x]));
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]){
         gswap(x,y);
    }
    Ans=max(Ans,On_Tree_query_max(1,1,n,go[x],go[y]));
    return Ans;
}
void On_Tree_build(ll n,ll nL,ll nR){
    if(nL==nR){
        sum[n]=back[nL];
        maxn[n]=back[nL];
    }else{
        ll M=(nL+nR)>>1;
        On_Tree_build(lc(n),nL,M);
        On_Tree_build(rc(n),M+1,nR);
        sum[n]=(sum[lc(n)]+sum[rc(n)]);
        maxn[n]=max(maxn[lc(n)],maxn[rc(n)]);
    }
}
void On_Tree_down(ll n,ll nL,ll nR){
    ll M=(nL+nR)>>1;
    sum[lc(n)]=(sum[lc(n)]+tag[n]*((M-nL+1)));
    maxn[lc(n)]=(maxn[lc(n)]+tag[n]);
    sum[rc(n)]=(sum[rc(n)]+tag[n]*((nR-M)));
    maxn[rc(n)]=(maxn[rc(n)]+tag[n]);
    tag[lc(n)]=(tag[lc(n)]+tag[n]);
    tag[rc(n)]=(tag[rc(n)]+tag[n]);
    tag[n]=0;
}
void On_Tree_update(ll n,ll nL,ll nR,ll uL,ll uR,ll num){
    if(nL>=uL&&nR<=uR){
        sum[n]=(sum[n]+(nR-nL+1)*num);
        maxn[n]=(maxn[n]+num);
        tag[n]=(tag[n]+num);
        return;
    }
    if(nR<uL||nL>uR){
        return;
    }
    On_Tree_down(n,nL,nR);
    ll M=(nL+nR)>>1;
    On_Tree_update(lc(n),nL,M,uL,uR,num);
    On_Tree_update(rc(n),M+1,nR,uL,uR,num);
    sum[n]=(sum[lc(n)]+sum[rc(n)]);
    maxn[n]=max(maxn[lc(n)],maxn[rc(n)]);
}
ll On_Tree_query_sum(ll n,ll nL,ll nR,ll qL,ll qR){
    if(nL>=qL&&nR<=qR){
        return sum[n];
    }
    if(nR<qL||nL>qR){
        return 0;
    }
    On_Tree_down(n,nL,nR);
    ll M=(nL+nR)>>1;
    return (On_Tree_query_sum(lc(n),nL,M,qL,qR)+On_Tree_query_sum(rc(n),M+1,nR,qL,qR));
}
ll On_Tree_query_max(ll n,ll nL,ll nR,ll qL,ll qR){
    if(nL>=qL&&nR<=qR){
        return maxn[n];
    }
    if(nR<qL||nL>qR){
        return -1000000000;
    }
    On_Tree_down(n,nL,nR);
    ll M=(nL+nR)>>1;
    return max(On_Tree_query_max(lc(n),nL,M,qL,qR),On_Tree_query_max(rc(n),M+1,nR,qL,qR));
}
