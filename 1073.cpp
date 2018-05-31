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
#define N 100005
#define Max 100000
#define inf 2147483647
#define M 1000005
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
class Edge{
public:
    int hed[N],to[M],nxt[M],id;
    void add(int ,int);
}fwd,bck;
int a[N];
int far[N],nar[N],que[N],flag[N],qh,qt;
int main(){
    int n,m,i,x,y,l,ans=0,u,v;
    read(n);
    read(m);
    for(i=1;i<=n;i++){
        read(a[i]);
        nar[i]=inf;
        far[i]=-inf;
    }
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        read(l);
        fwd.add(x,y);
        bck.add(y,x);
        if(l==2){
            fwd.add(y,x);
            bck.add(x,y);
        }
    }
    que[qh=0]=1;
    qt=1;
    flag[1]=true;
    nar[1]=a[1];
    while(qh!=qt){
        u=que[qh];
        qh=(qh+1)%Max;
        flag[u]=false;
        for(i=fwd.hed[u];i;i=fwd.nxt[i]){
            v=fwd.to[i];
            if(nar[v]>min(nar[u],a[v])){
                nar[v]=min(nar[u],a[v]);
                if(flag[v]==false){
                    que[qt]=v;
                    qt=(qt+1)%Max;
                    flag[v]=true;
                }
            }
        }
    }
    que[qh=0]=n;
    qt=1;
    flag[n]=true;
    far[n]=a[n];
    while(qh!=qt){
        u=que[qh];
        qh=(qh+1)%Max;
        flag[u]=false;
        for(i=bck.hed[u];i;i=bck.nxt[i]){
            v=bck.to[i];
            if(far[v]<max(far[u],a[v])){
                far[v]=max(far[u],a[v]);
                if(flag[v]==false){
                    que[qt]=v;
                    qt=(qt+1)%Max;
                    flag[v]=true;
                }
            }
        }
    }
    for(i=1;i<=n;i++){
        if(far[i]!=-inf&&nar[i]!=inf){
            ans=max(ans,far[i]-nar[i]);
        }
    }
    write(ans);
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
void Edge::add(int x,int y){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
}
