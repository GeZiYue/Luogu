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
#define N 105
#define M 15005
#define M_Q 100
#define inf 2147483647
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int,int,int,int);
bool SPFA();
int Min_Cost_Max_Flow();
int hed[N],nxt[M],to[M],flow[M],cost[M],id=1;
int que[N],qt,qh;
int dis[N],pre[N],ans[N];
int s,t;
bool flag[N];
int a[N];
int main(){
    int n,sum=0,i,arg;
    read(n);
    s=n+1;
    t=n+2;
    for(i=1;i<=n;i++){
        read(a[i]);
        sum+=a[i];
    }
    arg=sum/n;
    for(i=1;i<=n;i++){
        if(a[i]>arg){
            add(s,i,a[i]-arg,0);
            add(i,s,0,0);
        }
        if(a[i]<arg){
            add(i,t,arg-a[i],0);
            add(t,i,0,0);
        }
    }
    for(i=1;i<=n;i++){
        if(i^1){
            add(i,i-1,inf,1);
            add(i-1,i,0,-1);
        }
        if(i^n){
            add(i,i+1,inf,1);
            add(i+1,i,0,-1);
        }
    }
    add(1,n,inf,1);
    add(n,1,0,-1);
    add(n,1,inf,1);
    add(1,n,0,-1);
    write(Min_Cost_Max_Flow());
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
void add(int x,int y,int flownow,int costnow){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    flow[id]=flownow;
    cost[id]=costnow;
}
bool SPFA(){
    int i,now;
    for(i=1;i<=t;i++){
        dis[i]=inf;
        flag[i]=false;
    }
    qh=0;
    qt=1;
    que[1]=s;
    flag[s]=true;
    dis[s]=0;
    ans[s]=inf;
    while(qh!=qt){
        qh=(qh+1)%M_Q;
        now=que[qh];
        flag[now]=false;
        for(i=hed[now];i;i=nxt[i]){
            if(flow[i]&&dis[now]+cost[i]<dis[to[i]]){
                dis[to[i]]=dis[now]+cost[i];
                pre[to[i]]=i;
                ans[to[i]]=min(ans[now],flow[i]);
                if(flag[to[i]]==false){
                    qt=(qt+1)%M_Q;
                    que[qt]=to[i];
                    flag[to[i]]=true;
                }
            }
        }
    }
    return (dis[t]!=inf);
}
int Min_Cost_Max_Flow(){
    int now,sum=0;
    while(SPFA()){
        now=t;
        while(now!=s){
            flow[pre[now]]-=ans[t];
            flow[pre[now]^1]+=ans[t];
            now=to[pre[now]^1];
        }
        sum+=ans[t]*dis[t];
    }
    return sum;
}
