#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define N 300005
#define M 600005
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1& );
template<class T1>void write(T1 );
void add(int ,int );
void DFS1(int );
void DFS2(int );
void DFS3(int );
int LCA(int ,int );
int hed[N],nxt[M],to[M],id1;
int dep[N],siz[N],fa[N],son[N],top[N];
int sum[N];
int a[N];
int main(){
    int n,i,root,x,y,lca;
    read(n);
    for(i=1;i<=n;i++){
        read(a[i]);
    }
    for(i=1;i<n;i++){
        read(x);
        read(y);
        add(x,y);
        add(y,x);
    }
    root=a[1];
    fa[root]=0;
    dep[root]=1;
    DFS1(root);
    top[root]=root;
    DFS2(root);
    for(i=1;i<n;i++){
        x=a[i];
        y=a[i+1];
        lca=LCA(x,y);
        sum[x]++;
        sum[fa[y]]++;
        sum[lca]--;
        sum[fa[lca]]--;
    }
    DFS3(root);
    for(i=1;i<=n;i++){
        write(sum[i]);
        EL;
    }
    return 0;
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
void add(int x,int y){
    nxt[++id1]=hed[x];
    hed[x]=id1;
    to[id1]=y;
}
void DFS1(int u){
    int i,v;
    siz[u]=1;
    for(i=hed[u];i;i=nxt[i]){
        v=to[i];
        if(v==fa[u]){
            continue;
        }
        dep[v]=dep[u]+1;
        fa[v]=u;
        DFS1(v);
        siz[u]+=siz[v];
        if(son[u]==0 || siz[v]>siz[son[u]]){
            son[u]=v;
        }
    }
}
void DFS2(int u){
    int i,v;
    for(i=hed[u];i;i=nxt[i]){
        v=to[i];
        if(v==fa[u]){
            continue;
        }
        top[v]=(v==son[u])?top[u]:v;
        DFS2(v);
    }
}
void DFS3(int u){
    int i,v;
    for(i=hed[u];i;i=nxt[i]){
        v=to[i];
        if(v==fa[u]){
            continue;
        }
        DFS3(v);
        sum[u]+=sum[v];
    }
}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]){
        swap(x,y);
    }
    return x;
}
