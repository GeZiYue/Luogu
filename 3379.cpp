#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define N 500005
int hed[N],nxt[2*N],to[2*N],dep[N],siz[N],son[N],top[N],fa[N];
int num;
void read(int &r_e_a_d);
void add(int x,int y);
void dfs1(int x);
void dfs2(int x);
int LCA(int x,int y);
int main(){
    int n,m,k,a,b,i;
    read(n);
    read(m);
    read(k);
    for(i=1;i<n;i++){
        read(a);
        read(b);
        add(a,b);
        add(b,a);
    }
    dfs1(k);
    top[k]=k;
    dfs2(k);
    for(i=1;i<=m;i++){
        read(a);
        read(b);
        cout<<LCA(a,b)<<endl;
    }
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
    register int i,v;
    siz[x]=1;
    dep[x]=dep[fa[x]]+1;
    for(i=hed[x];i;i=nxt[i]){
        v=to[i];
        if(v!=fa[x]){
            fa[v]=x;
            dfs1(v);
            siz[x]+=siz[v];
            if(son[x]==-1||siz[v]>siz[son[x]]){
                son[x]=v;
            }
        }
    }
}
void dfs2(int x){
    register int i,v;
    if(son[x]==0){
        return;
    }
    top[son[x]]=top[x];
    dfs2(son[x]);
    for(i=hed[x];i;i=nxt[i]){
        v=to[i];
        if(v!=son[x]&&v!=fa[x]){
            top[v]=v;
            dfs2(v);
        }
    }
    return;
}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]){
            x=fa[top[x]];
        }else{
            y=fa[top[y]];
        }
    }
    return dep[x]<dep[y]?x:y;
}
