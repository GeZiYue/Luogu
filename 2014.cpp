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
#define N 305
#define M 305
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int ,int );
int DFS(int );
int hed[N],nxt[M],to[M],id;
int dp[N][N];
int a[N];
int n,m;
int main(){
    int x,i;
    read(n);
    read(m);
    for(i=1;i<=n;i++){
        read(x);
        read(a[i]);
        if(x==0){
            x=n+1;
        }
        add(x,i);
    }
    DFS(n+1);
    write(dp[n+1][m]);
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
void add(int x,int y){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
}
int DFS(int u){
    int i,j,k,v,size=1,now;
    dp[u][0]=a[u];
    for(i=hed[u];i;i=nxt[i]){
        v=to[i];
        now=DFS(v);
        size+=now;
        for(j=m;j>=0;j--){
            for(k=0;k<=now&&j-k>=1;k++){
                dp[u][j]=max(dp[u][j],dp[u][j-k-1]+dp[v][k]);
            }
        }
    }
    return size;
}
