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
#define N 6005
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int x,int y);
void DP(int x,int fa);
int dp1[N],dp2[N];
int hed[N],nxt[2*N],to[2*N],id;
int a[N];
int main(){
    int n,i,x,y;
    read(n);
    for(i=1;i<=n;i++){
        read(a[i]);
    }
    for(i=1;i<n;i++){
        read(x);
        read(y);
        add(x,y);
        add(y,x);
    }
    DP(1,0);
    write(max(dp1[1],dp2[1]));
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
void DP(int x,int fa){
    dp1[x]=0;
    dp2[x]=a[x];
    int i;
    for(i=hed[x];i;i=nxt[i]){
        if(to[i]==fa){
            continue;
        }
        DP(to[i],x);
        dp1[x]+=max(dp1[to[i]],dp2[to[i]]);
        dp2[x]+=dp1[to[i]];
    }
}
