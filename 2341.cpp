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
#define N 10005
#define M 50005
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void tarjan(int);
void add(int,int);
int hed[N],nxt[M],to[M],id;
int stamp,dfn[N],low[N],s[N],belong[N],sum[N],o[N],top,group;
bool vis[N];
int main(){
    int n,m,i,j,x,y,ans=0;
    read(n);
    read(m);
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        add(x,y);
    }
    for(i=1;i<=n;i++){
        if(dfn[i]==0){
            tarjan(i);
        }
    }
    for(i=1;i<=n;i++){
        for(j=hed[i];j;j=nxt[j]){
            if(belong[i]!=belong[to[j]]){
                o[belong[i]]++;
            }
        }
    }
    for(i=1;i<=group;i++){
        if(o[i]==0){
            if(ans!=0){
                puts("0");
                return 0;
            }else{
                ans=i;
            }
        }
    }
    write(sum[ans]);
    EL;
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
void tarjan(int x){
    int i,k;
    dfn[x]=low[x]=++stamp;
    s[++top]=x;
    vis[x]=true;
    for(i=hed[x];i;i=nxt[i]){
        if(!dfn[to[i]]){
            tarjan(to[i]);
            low[x]=min(low[x],low[to[i]]);
        }else{
            if(vis[to[i]]){
                low[x]=min(low[x],dfn[to[i]]);
            }
        }
    }
    if(dfn[x]==low[x]){
        group++;
        while(1){
            k=s[top];
            top--;
            belong[k]=group;
            vis[k]=false;
            sum[group]++;
            if(k==x){
                break;
            }
        }
    }
}
void add(int x,int y){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
}
