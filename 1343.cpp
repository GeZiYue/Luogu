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
#define N 205
#define M 2005
#define ll long long int
#define inf 2147483647
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int x,int y,int flownow);
bool Max_Flow_BFS();
ll Max_Flow_DFS(int x,int minn);
void Max_Flow_Dinic();
int s,t,n;
int hed[N],nxt[2*M],to[2*M],flow[2*M],id=1;
int dep[N],cur[N];
int que[N],qh,qt;
ll Max_Flow;
int main(){
    ll m,k,x,y,flownow,i;
    read(n);
    read(m);
    read(k);
    s=1;
    t=n;
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        read(flownow);
        add(x,y,flownow);
        add(y,x,0);
    }
    Max_Flow_Dinic();
    if(Max_Flow==0){
        puts("Orz Ni Jinan Saint Cow!");
        return 0;
    }
    write(Max_Flow);
    SP;
    write((k+Max_Flow-1)/Max_Flow);
    EL;
    return 0;
}
void add(int x,int y,int flownow){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    flow[id]=flownow;
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
bool Max_Flow_BFS(){
    int i,now;
    for(i=1;i<=n;i++){
        dep[i]=inf;
        cur[i]=hed[i];
    }
    dep[s]=0;
    que[qh=qt=1]=s;
    while(qh<=qt){
        now=que[qh++];
        for(i=hed[now];i;i=nxt[i]){
            if(flow[i]&&dep[to[i]]==inf){
                dep[to[i]]=dep[now]+1;
                que[++qt]=to[i];
            }
        }
    }
    return (dep[t]!=inf);
}
ll Max_Flow_DFS(int x,int minn){
    if(minn==0||x==t){
        return minn;
    }
    int i,now;
    ll result=0;
    for(i=cur[x];i;i=nxt[i]){
        cur[x]=i;
        if(dep[to[i]]!=dep[x]+1){
            continue;
        }
        now=Max_Flow_DFS(to[i],min(minn,flow[i]));
        if(now){
            result+=now;
            minn-=now;
            flow[i]-=now;
            flow[i^1]+=now;
            if(minn==0){
                break;
            }
        }
    }
    return result;
}
void Max_Flow_Dinic(){
    while(Max_Flow_BFS()){
        Max_Flow+=Max_Flow_DFS(s,inf);
    }
}
