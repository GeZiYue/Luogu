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
#define M 1000005
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int x,int y);
bool Try(int x);
int hed[N],nxt[M],to[M];
bool use[N];
int match[N];
int id;
int main(){
    int n,m,k,i,a,b,ans=0;
    read(n);
    read(m);
    read(k);
    for(i=1;i<=k;i++){
        read(a);
        read(b);
        if(a<=n&&b<=m){
            add(a,b);
        }
    }
    for(i=1;i<=n;i++){
        memset(use,0,sizeof(use));
        ans+=Try(i);
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
        ch=getchar();
        if(ch=='-'){
            flag=-1;
        }
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
bool Try(int x){
    int i;
    for(i=hed[x];i;i=nxt[i]){
        if(!use[to[i]]){
            use[to[i]]=1;
            if(!match[to[i]]||Try(match[to[i]])){
                match[to[i]]=x;
                return 1;
            }
        }
    }
    return 0;
}
