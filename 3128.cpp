#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define N 50005
#define lc(n) (n<<1)
#define rc(n) (lc(n)|1)
int hed[N],nxt[2*N],to[2*N],dep[N],siz[N],son[N],top[N],fa[N],Tree[N];
int maxn[4*N],tag[4*N];
int n;
int num,tim;
void read(int &r_e_a_d);
void add(int x,int y);
void dfs1(int x);
void dfs2(int x,int tp);
void update(int x,int y);
void down(int n);
void Tree_update(int n,int nL,int nR,int uL,int uR);
int main(){
    int m,i,a,b;
    read(n);
    read(m);
    for(i=1;i<n;i++){
        read(a);
        read(b);
        add(a,b);
        add(b,a);
    }
    dfs1(1);
    dfs2(1,1);
    for(i=1;i<=m;i++){
        read(a);
        read(b);
        update(a,b);
    }
    cout<<maxn[1]<<endl;
}
void read(int &r_e_a_d){
    int k=0;
    bool flag=0;
    char c;
    while(1){
        c=getchar();
        if(c=='-'){
            flag=1;
            break;
        }
        if(c>='0'&&c<='9'){
            k=c-'0';
            break;
        }
    }
    while(1){
        c=getchar();
        if(c<'0'||c>'9'){
            break;
        }else{
            k=(k<<1)+(k<<3)+c-'0';
        }
    }
    if(flag==1){
        k=-k;
    }
    r_e_a_d=k;
}
void add(int x,int y){
    to[++num]=y;
    nxt[num]=hed[x];
    hed[x]=num;
}
void dfs1(int x){
    register int i,y;
    siz[x]=1;
    son[x]=0;
    for(i=hed[x];i;i=nxt[i]){
        y=to[i];
        if(y!=fa[x]){
            fa[y]=x;
            dep[y]=dep[x]+1;
            dfs1(y);
            siz[x]+=siz[y];
            if(son[x]==0||siz[y]>siz[son[x]]){
                son[x]=y;
            }
        }
    }
}
void dfs2(int x,int tp){
    register int i,y;
    top[x]=tp;
    Tree[x]=++tim;
    if(son[x]==0){
        return;
    }
    dfs2(son[x],tp);
    for(i=hed[x];i;i=nxt[i]){
        y=to[i];
        if(y!=son[x]&&y!=fa[x]){
            dfs2(y,y);
        }
    }
    return;
}
void update(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        Tree_update(1,1,n,Tree[top[x]],Tree[x]);
        x=fa[top[x]];
    }
    if(Tree[x]>Tree[y]){
        swap(x,y);
    }
    Tree_update(1,1,n,Tree[x],Tree[y]);
}
void Tree_update(int n,int nL,int nR,int uL,int uR){
    if(nL>=uL&&nR<=uR){
        maxn[n]++;
        tag[n]++;
        return;
    }
    if(nR<uL||nL>uR){
        return;
    }
    down(n);
    int M=(nL+nR)>>1;
    Tree_update(lc(n),nL,M,uL,uR);
    Tree_update(rc(n),M+1,nR,uL,uR);
    maxn[n]=max(maxn[lc(n)],maxn[rc(n)]);
}
void down(int n){
    maxn[lc(n)]+=tag[n];
    maxn[rc(n)]+=tag[n];
    tag[lc(n)]+=tag[n];
    tag[rc(n)]+=tag[n];
    tag[n]=0;
}
