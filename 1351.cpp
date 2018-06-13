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
#define N 200005
#define M 400005
#define Mod 10007
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int ,int );
void DFS(int ,int );
int hed[N],nxt[M],to[M],id;
int a[N];
int maxn,sum;
int main(){
    int n,i,x,y;
    read(n);
    for(i=1;i<n;i++){
        read(x);
        read(y);
        add(x,y);
        add(y,x);
    }
    for(i=1;i<=n;i++){
        read(a[i]);
    }
    DFS(1,0);
    write(maxn);
    SP;
    write(sum);
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
void DFS(int u,int fa){
    int v,i,max1=0,max2=0,ans=0,num=0;
    for(i=hed[u];i;i=nxt[i]){
        v=to[i];
        if(v==fa){
            break;
        }
        if(a[v]>max1){
            max2=max1;
            max1=a[v];
        }else{
            if(a[v]>max2){
                max2=a[v];
            }
        }
        ans=(ans+a[v])%Mod;
        num=(num+(a[v]*a[v])%Mod)%Mod;
        maxn=max(maxn,a[v]*a[fa]);
        sum=(sum+a[v]*a[fa])%Mod;
        sum=(sum+a[v]*a[fa])%Mod;
        DFS(v,u);
    }
    maxn=max(maxn,max1*max2);
    sum=(sum+(ans*ans%Mod+Mod-num)%Mod)%Mod;
}
