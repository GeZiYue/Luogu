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
#define M 10005
#define inf 2147483647
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int x,int y,int flownow);
bool Max_Flow_BFS();
int Max_Flow_DFS(int,int);
int Max_Flow_Dinic();
int hed[N],cur[N],nxt[2*M],to[2*M],flow[2*M],id=1;
int que[N],qh,qt;
int dep[N];
int s,t,e;
int main(){
    int n,m,x,y,i,j;
    read(n);
    read(m);
    while(1){
        read(x);
        read(y);
        if(x==-1&&y==-1){
            break;
        }
        add(x,y,1);
        add(y,x,0);
    }
    e=m+2;
    s=m+1;
    for(i=1;i<=n;i++){
        add(s,i,1);
        add(i,s,0);
    }
    t=m+2;
    for(i=n+1;i<=m;i++){
        add(i,t,1);
        add(t,i,0);
    }
    write(Max_Flow_Dinic());
    EL;
    for(i=1;i<=n;i++){
        for(j=hed[i];j;j=nxt[j]){
            if(to[j]>n&&to[j]<=m&&flow[j]==0){
                write(i);
                SP;
                write(to[j]);
                EL;
            }
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
void add(int x,int y,int flownow){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    flow[id]=flownow;
}
bool Max_Flow_BFS(){
    int i,x;
    for(i=1;i<=e;i++){
        dep[i]=inf;
        cur[i]=hed[i];
    }
    dep[s]=0;
    que[qh=qt=1]=s;
    while(qh<=qt){
        x=que[qh++];
        for(i=hed[x];i;i=nxt[i]){
            if(flow[i]>0&&dep[to[i]]==inf){
                dep[to[i]]=dep[x]+1;
                que[++qt]=to[i];
            }
        }
    }
    return (dep[t]^inf);
}
int Max_Flow_DFS(int x,int minn){
    if(minn==0||x==t){
        return minn;
    }
    int i,now,ans=0;
    for(i=cur[x];i;i=nxt[i]){
        cur[x]=i;
        if(dep[to[i]]!=dep[x]+1){
            continue;
        }
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
    return ans;
}
int Max_Flow_Dinic(){
    int ans=0;
    while(Max_Flow_BFS()){
        ans+=Max_Flow_DFS(s,inf);
    }
    return ans;
}
