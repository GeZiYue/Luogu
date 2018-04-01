#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define N 100005
int hed[N],nxt[2*N],to[2*N],len[2*N],dep[N],siz[N],son[N],top[N],fa[N],dis[N];
int num;
void read(int &r_e_a_d);
void add(int x,int y,int z);
void dfs1(int x,int father,int disx);
void dfs2(int x,int tp);
int LCA(int x,int y);
int main(){
    int n,m,a,b,c,i;
    read(n);
    read(m);
    for(i=1;i<n;i++){
        read(a);
        read(b);
        read(c);
        add(a,b,c);
        add(b,a,c);
    }
    dfs1(1,1,0);
    dfs2(1,1);
    for(i=1;i<=m;i++){
        read(a);
        read(b);
        cout<<dis[a]+dis[b]-2*dis[LCA(a,b)]<<endl;
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
void add(int x,int y,int z){
    to[++num]=y;
    nxt[num]=hed[x];
    hed[x]=num;
    len[num]=z;
}
void dfs1(int x,int father,int disx){
    register int i,v;
    siz[x]=1;
    fa[x]=father;
    dep[x]=dep[father]+1;
    dis[x]=disx;
    for(i=hed[x];i;i=nxt[i]){
        v=to[i];
        if(v!=father){
            dfs1(v,x,disx+len[i]);
            siz[x]+=siz[v];
            if(son[x]==-1||siz[v]>siz[son[x]]){
                son[x]=v;
            }
        }
    }
}
void dfs2(int x,int tp){
    register int i,v;
    top[x]=tp;
    if(son[x]==0){
        return;
    }
    dfs2(son[x],tp);
    for(i=hed[x];i;i=nxt[i]){
        v=to[i];
        if(v!=son[x]&&v!=fa[x]){
            dfs2(v,v);
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
