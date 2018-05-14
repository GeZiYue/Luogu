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
#define M 20005
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int,int,int);
bool SPFA(int);
int hed[N],nxt[M],to[M],dis[M],id;
int far[N];
bool vis[N];
int main(){
    int n,m,i,a,x,y,diss;
    read(n);
    read(m);
    for(i=1;i<=m;i++){
        read(a);
        read(x);
        read(y);
        if(a==1){
            read(diss);
            add(x,y,-diss);
        }else{
            if(a==2){
                read(diss);
                add(x,y,diss);
            }else{
                add(x,y,0);
                add(y,x,0);
            }
        }
    }
    for(i=1;i<=n;i++){
        dis[i]=0;
        if(!SPFA(i)){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
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
bool SPFA(int n){
    int i;
    vis[n]=true;
    for(i=hed[n];i;i=nxt[i]){
        if(far[n]+dis[i]<far[to[i]]){
            far[to[i]]=far[n]+dis[i];
            if(vis[to[i]]){
                return false;
            }
            if(!SPFA(to[i])){
                return false;
            }
        }
    }
    vis[n]=false;
    return true;
}
