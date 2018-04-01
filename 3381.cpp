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
#define N 5005
#define M 50005
#define inf 2147483647
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int x,int y,int flownow,int costnow);
bool BFS();
void Max_Flow();
int que[2*M],qh,qt;
int hed[N],nxt[2*M],to[2*M],cost[2*M],flow[2*M],id=1;
int n,s,t;
int maxflow,mincost;
int dis[N],fin[N],ans[N];
bool flag[N];
int main(){
    int m,x,y,flownow,costnow,i;
    read(n);
    read(m);
    read(s);
    read(t);
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        read(flownow);
        read(costnow);
        add(x,y,flownow,costnow);
        add(y,x,0,-costnow);
    }
    Max_Flow();
    write(maxflow);
    SP;
    write(mincost);
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
bool BFS(){
    int i,now;
    for(i=1;i<=n;i++){
        dis[i]=inf;
        flag[i]=false;
    }
    que[qh=qt=1]=s;
    dis[s]=0;
    ans[s]=inf;
    flag[s]=true;
    while(qh<=qt){
        now=que[qh++];
        flag[now]=false;
        for(i=hed[now];i;i=nxt[i]){
            if(flow[i]>0&&dis[to[i]]>dis[now]+cost[i]){
                ans[to[i]]=min(ans[now],flow[i]);
                dis[to[i]]=dis[now]+cost[i];
                fin[to[i]]=i;
                if(flag[to[i]]==false){
                    flag[to[i]]=true;
                    que[++qt]=to[i];
                }
            }
        }
    }
    return dis[t]!=inf;
}
void Max_Flow(){
    int now;
    while(BFS()){
        now=t;
        while(now^s){
            flow[fin[now]]-=ans[t];
            flow[fin[now]^1]+=ans[t];
            now=to[fin[now]^1];
        }
        maxflow+=ans[t];
        mincost+=ans[t]*dis[t];
    }
}
