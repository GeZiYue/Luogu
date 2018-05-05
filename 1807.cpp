#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define N 1505
#define M 50005
#define inf 1000000000
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int,int,int);
int vis[N];
int hed[N],nxt[M],to[M],dis[M],id;
int far[N];
queue<int>q;
int main(){
    int n,m,i,x,y,diss,now;
    read(n);
    read(m);
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        read(diss);
        add(x,y,diss);
    }
    for(i=1;i<=n;i++){
        far[i]=-inf;
    }
    q.push(1);
    far[1]=0;
    vis[1]=true;
    while(!q.empty()){
        now=q.front();
        q.pop();
        for(i=hed[now];i;i=nxt[i]){
            if(far[now]+dis[i]>far[to[i]]){
                far[to[i]]=far[now]+dis[i];
                if(vis[to[i]]==false){
                    q.push(to[i]);
                }
            }
        }
        vis[now]=false;
    }
    if(far[n]==-inf){
        far[n]=-1;
    }
    write(far[n]);
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
void add(int x,int y,int diss){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    dis[id]=diss;
}
