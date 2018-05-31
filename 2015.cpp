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
#define M 205
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int ,int ,int);
int dfs(int ,int);
int dp[N][N];
int hed[N],to[M],nxt[M],dis[M],id;
int m;
int main(){
    int n,i,x,y,diss;
    read(n);
    read(m);
    for(i=1;i<n;i++){
        read(x);
        read(y);
        read(diss);
        add(x,y,diss);
        add(y,x,diss);
    }
    dfs(1,0);
    write(dp[1][m]);
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
void add(int x,int y,int diss){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    dis[id]=diss;
}
int dfs(int x,int fa){
    int size=0,i,j,k;
    for(i=hed[x];i;i=nxt[i]){
        if(to[i]==fa){
            continue;
        }
        size+=dfs(to[i],x)+1;
        for(j=min(m,size);j>0;j--){
            for(k=j;k>0;k--){
                dp[x][j]=max(dp[x][j],dp[x][j-k]+dp[to[i]][k-1]+dis[i]);
            }
        }
    }
    return size;
}
