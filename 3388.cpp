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
#define N 100000
#define M 100000
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int,int);
void Tarjan(int);
int hed[N+5],nxt[2*M+5],to[2*M+5],id1;
int low[N+5],dfn[N+5],id2;
int root;
bool flag[N+5];
int main(){
    int n,m,x,y,i,ans=0;
    read(n);
    read(m);
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        add(x,y);
        add(y,x);
    }
    for(i=1;i<=n;i++){
        if(!dfn[i]){
            root=i;
            Tarjan(i);
        }
    }
    for(i=1;i<=n;i++){
        if(flag[i]){
            ans++;
        }
    }
    write(ans);
    EL;
    for(i=1;i<=n;i++){
        if(flag[i]){
            write(i);
            SP;
        }
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
void Tarjan(int u){
    int sum=0,i,v;
    low[u]=dfn[u]=++id2;
    for(i=hed[u];i;i=nxt[i]){
        v=to[i];
        if(!dfn[v]){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
            if(u==root){
                sum++;
            }else{
                flag[u]=flag[u]||(low[v]>=dfn[u]);
            }
        }
        low[u]=min(low[u],dfn[v]);
    }
    if(u==root){
        flag[u]=(sum>=2);
    }
}
