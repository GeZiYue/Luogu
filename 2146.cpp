#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define N 100005
#define lc(a) (a<<1)
#define rc(a) (lc(a)|1)
#define g(a,b) (a^=b^=a^=b)
int num[N],siz[N],dep[N],son[N],fa[N],top[N];
int hed[N],nxt[N],to[N];
int sum[4*N],tag[4*N];
int id1,id2;
int n;
char arg[15];
template<class T1>
    void read(T1& r_e_a_d);
template<class T1>
    void write(T1 w_r_i_t_e);
void add(int x,int y);
void DFS1(int x);
void DFS2(int x);
int install(int x);
int uninstall(int x);
void down(int n,int nL,int nR);
void Tree_install(int n,int nL,int nR,int uL,int uR);
void Tree_uninstall(int n,int nL,int nR,int uL,int uR);
int main(){
    int m,i,a;
    read(n);
    for(i=2;i<=n;i++){
        read(a);
        a++;
        add(a,i);
    }
    dep[1]=1;
    DFS1(1);
    top[1]=1;
    DFS2(1);
    read(m);
    for(i=1;i<=m;i++){
        cin>>arg;
        read(a);
        a++;
        if(strcmp(arg,"install")==0){
            write(install(a));
            putchar('\n');
        }else{
            write(uninstall(a));
            putchar('\n');
        }
    }
    return 0;
}
template<class T1>
    void read(T1& r_e_a_d){
        T1 k;
        char ch;
        bool flag=0;
        while(1){
            ch=getchar();
            if(ch=='-'){
                flag=1;
            }
            if(ch>='0'&&ch<='9'){
                k=ch-'0';
                break;
            }
        }
        while(1){
            ch=getchar();
            if(ch<'0'||ch>'9'){
                break;
            }else{
                k=(k<<1)+(k<<3)+ch-'0';
            }
        }
        if(flag){
            r_e_a_d=-k;
        }else{
            r_e_a_d=k;
        }
    }
template<class T1>
    void write(T1 w_r_i_t_e){
        if(w_r_i_t_e<10){
            putchar(w_r_i_t_e+'0');
        }else{
            write(w_r_i_t_e/10);
            putchar(w_r_i_t_e%10+'0');
        }
    }
void add(int x,int y){
    nxt[++id1]=hed[x];
    hed[x]=id1;
    to[id1]=y;
}
void DFS1(int x){
    siz[x]=1;
    son[x]=0;
    for(int i=hed[x];i;i=nxt[i]){
        fa[to[i]]=x;
        dep[to[i]]=dep[x]+1;
        DFS1(to[i]);
        siz[x]+=siz[to[i]];
        if(son[x]==0||siz[to[i]]>siz[son[x]]){
            son[x]=to[i];
        }
    }
}
void DFS2(int x){
    num[x]=++id2;
    if(son[x]){
        top[son[x]]=top[x];
        DFS2(son[x]);
    }
    for(int i=hed[x];i;i=nxt[i]){
        if(to[i]!=son[x]){
            top[to[i]]=to[i];
            DFS2(to[i]);
        }
    }
}
int install(int x){
    int bef=sum[1];
    int a=x,b=1;
    while(top[a]!=top[b]){
        if(dep[a]<dep[b]){
            g(a,b);
        }
        Tree_install(1,1,n,num[top[a]],num[a]);
        a=fa[top[a]];
    }
    if(dep[a]>dep[b]){
        g(a,b);
    }
    Tree_install(1,1,n,num[a],num[b]);
    return (sum[1]-bef);
}
int uninstall(int x){
    int bef=sum[1];
    Tree_uninstall(1,1,n,num[x],num[x]+siz[x]-1);
    return (bef-sum[1]);
}
void down(int n,int nL,int nR){
    int M=(nL+nR)>>1;
    if(tag[n]==1){
        tag[lc(n)]=1;
        tag[rc(n)]=1;
        sum[lc(n)]=(M-nL+1);
        sum[rc(n)]=(nR-M);
    }
    if(tag[n]==-1){
        tag[lc(n)]=-1;
        tag[rc(n)]=-1;
        sum[lc(n)]=0;
        sum[rc(n)]=0;
    }
    tag[n]=0;
}
void Tree_install(int n,int nL,int nR,int uL,int uR){
    if(nL>=uL&&nR<=uR){
        tag[n]=1;
        sum[n]=nR-nL+1;
        return;
    }
    if(nR<uL||nL>uR){
        return;
    }
    down(n,nL,nR);
    int M=(nL+nR)>>1;
    Tree_install(lc(n),nL,M,uL,uR);
    Tree_install(rc(n),M+1,nR,uL,uR);
    sum[n]=sum[lc(n)]+sum[rc(n)];
}
void Tree_uninstall(int n,int nL,int nR,int uL,int uR){
    if(nL>=uL&&nR<=uR){
        tag[n]=-1;
        sum[n]=0;
        return;
    }
    if(nR<uL||nL>uR){
        return;
    }
    down(n,nL,nR);
    int M=(nL+nR)>>1;
    Tree_uninstall(lc(n),nL,M,uL,uR);
    Tree_uninstall(rc(n),M+1,nR,uL,uR);
    sum[n]=sum[lc(n)]+sum[rc(n)];
}
