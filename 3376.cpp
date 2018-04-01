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
#define M 100005
#define inf 2147483647
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void Add(int x,int y,int now);
bool Max_Flow_BFS();
int Max_Flow_DFS(int x,int minn);
int Max_Flow_Dinic();
int hed[N],cur[N],nxt[2*M],to[2*M],flow[2*M],id=1;
int que[N],qh,qt;
int dep[N];
int s,t,n;
int main(){
    int m,i,x,y,now;
    read(n);
    read(m);
    read(s);
    read(t);
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        read(now);
        Add(x,y,now);
        Add(y,x,0);
    }
    write(Max_Flow_Dinic());
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
void Add(int x,int y,int now){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    flow[id]=now;
}
bool Max_Flow_BFS(){
    int i,x;
    for(i=1;i<=n;i++){
        dep[i]=inf;
        cur[i]=hed[i];
    }
    dep[s]=0;
    qh=qt=1;
    que[1]=s;
    while(qh<=qt){
        x=que[qh];
        qh++;
        for(i=hed[x];i;i=nxt[i]){
            if(dep[to[i]]==inf&&flow[i]){
                dep[to[i]]=dep[x]+1;
                que[++qt]=to[i];
            }
        }
    }
    if(dep[t]==inf){
        return 0;
    }else{
        return 1;
    }
}
int Max_Flow_DFS(int x,int minn){
    if(minn==0||x==t){
        return minn;
    }
    int result=0,now;
    int i;
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
int Max_Flow_Dinic(){
    int ans=0;
    while(Max_Flow_BFS()){
        ans+=Max_Flow_DFS(s,inf);
    }
    return ans;
}
