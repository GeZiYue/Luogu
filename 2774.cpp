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
#define M 50005
#define inf 2147483647
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int x,int y,int flownow);
bool Max_Flow_BFS();
int Max_Flow_DFS(int x,int minn);
int Max_Flow_Dinic();
int s,t;
int hed[M],nxt[M],to[M],flow[M],id=1;
int xx[10]={0,1,-1,0,0},yy[10]={0,0,0,1,-1};
int dep[M];
int que[M],qh,qt;
int main(){
    int n,m,i,j,k,a,sum=0;
    int nx,ny;
    read(n);
    read(m);
    s=n*m+1;
    t=n*m+2;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            read(a);
            if(((i+j)&1)==0){
                add(s,(i-1)*m+j,a);
                add((i-1)*m+j,s,0);
            }else{
                add((i-1)*m+j,t,a);
                add(t,(i-1)*m+j,0);
            }
            sum+=a;
        }
    }
    for(i=1;i<=n;i++){
        for(j=((i-1)&1)+1;j<=m;j+=2){
            for(k=1;k<=4;k++){
                nx=i+xx[k];
                ny=j+yy[k];
                if(nx>=1&&ny>=1&&nx<=n&&ny<=m){
                    add((i-1)*m+j,(nx-1)*m+ny,inf);
                    add((nx-1)*m+ny,(i-1)*m+j,0);
                }
            }
        }
    }
    write(sum-Max_Flow_Dinic());
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
    int now,i;
    for(i=1;i<=t;i++){
        dep[i]=inf;
    }
    que[qh=qt=1]=s;
    dep[s]=0;
    while(qh<=qt){
        now=que[qh++];
        for(i=hed[now];i;i=nxt[i]){
            if(dep[to[i]]==inf&&flow[i]){
                dep[to[i]]=dep[now]+1;
                que[++qt]=to[i];
            }
        }
    }
    return dep[t]!=inf;
}
int Max_Flow_DFS(int x,int minn){
    if(x==t||minn==0){
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
