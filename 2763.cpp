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
#define N 2005
#define M 30005
#define inf 2147483647
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int,int,int);
bool Max_Flow_BFS();
int Max_Flow_DFS(int,int);
int Max_Flow_Dinic();
int hed[N],nxt[M],to[M],flow[M],id=1;
int dep[N];
int que[N],qh,qt;
int a[25];
int s,t;
int main(){
    int n,m,i,j,x,q,sum=0;
    read(n);
    read(m);
    s=n+m+1;
    t=n+m+2;
    for(i=1;i<=n;i++){
        read(a[i]);
        sum+=a[i];
    }
    for(i=1;i<=m;i++){
        read(q);
        for(j=1;j<=q;j++){
            read(x);
            add(i+n,x,1);
            add(x,i+n,0);
        }
    }
    for(i=1;i<=n;i++){
        add(i,t,a[i]);
        add(t,i,0);
    }
    for(i=1;i<=m;i++){
        add(s,i+n,1);
        add(i+n,s,0);
    }
    if(Max_Flow_Dinic()<sum){
        puts("No Solution!");
        return 0;
    }
    for(i=1;i<=n;i++){
        write(i);
        putchar(':');
        SP;
        for(j=hed[i];j;j=nxt[j]){
            if(flow[j]==1){
                write(to[j]-n);
                SP;
            }
        }
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
void add(int x,int y,int flownow){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    flow[id]=flownow;
}
bool Max_Flow_BFS(){
    int i,now;
    for(i=1;i<=t;i++){
        dep[i]=inf;
    }
    dep[s]=0;
    que[qh=qt=1]=s;
    while(qh<=qt){
        now=que[qh++];
        for(i=hed[now];i;i=nxt[i]){
            if(dep[to[i]]==inf&&flow[i]){
                dep[to[i]]=dep[now]+1;
                que[++qt]=to[i];
            }
        }
    }
    return (dep[t]!=inf);
}
int Max_Flow_DFS(int x,int minn){
    if(minn==0||x==t){
        return minn;
    }
    int i,now,ans=0;
    for(i=hed[x];i;i=nxt[i]){
        if(dep[to[i]]==dep[x]+1){
            now=Max_Flow_DFS(to[i],min(minn,flow[i]));
            if(now){
                ans+=now;
                minn-=now;
                flow[i]-=now;
                flow[i^1]+=now;
                if(minn==0){
                    break;
                }
            }
        }
    }
    return ans;
}
int Max_Flow_Dinic(){
    int ans=0;
    while(Max_Flow_BFS()){
        ans+=Max_Flow_DFS(s,inf);
    }
    return ans;
}
