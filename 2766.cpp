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
#define N 1005
#define M 2000005
#define inf 2147483647
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int,int,int);
bool Max_Flow_BFS();
int Max_Flow_DFS(int,int);
int Max_Flow_Dinic();
int a[N],dp[N];
int s,t;
int hed[N],cur[N],nxt[M],to[M],flow[M],id=1;
int que[N],qh,qt;
int dep[N];
int ans;
int main(){
    int n,i,j,maxlen=0;
    read(n);
    for(i=1;i<=n;i++){
        read(a[i]);
        dp[i]=1;
        for(j=1;j<i;j++){
            if(a[j]<=a[i]){
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
        maxlen=max(maxlen,dp[i]);
    }
    write(maxlen);
    EL;
    s=1001;
    t=1002;
    for(i=1;i<=n;i++){
        if(dp[i]==1){
            add(s,i,1);
            add(i,s,0);
        }
        if(dp[i]==maxlen){
            add(i+n,t,1);
            add(t,i+n,0);
        }
        add(i,i+n,1);
        add(i+n,i,0);
        for(j=1;j<i;j++){
            if(a[j]<=a[i]&&dp[j]+1==dp[i]){
                add(j+n,i,1);
                add(i,j+n,0);
            }
        }
    }
    write(Max_Flow_Dinic());
    EL;
    add(s,1,inf);
    add(1,s,0);
    add(1,1+n,inf);
    add(1+n,1,0);
    if(dp[n]==maxlen){
        add((n<<1),t,inf);
        add(t,(n<<1),0);
        add(n,(n<<1),inf);
        add((n<<1),n,0);
    }
    write(Max_Flow_Dinic());
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
void add(int x,int y,int flownow){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    flow[id]=flownow;
}
bool Max_Flow_BFS(){
    int i,now;
    for(i=1;i<=t;i++){
        cur[i]=hed[i];
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
    for(i=cur[x];i;i=nxt[i]){
        cur[x]=i;
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
    while(Max_Flow_BFS()){
        ans+=Max_Flow_DFS(s,inf);
    }
    return ans;
}
