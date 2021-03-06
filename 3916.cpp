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
#define M 100005
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int x,int y);
int hed[N],nxt[M],to[M],id;
int ans[N];
int que[N],qh,qt;
int main(){
    int n,m,i,j,now,x,y;
    read(n);
    read(m);
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        add(y,x);
    }
    for(i=n;i>=1;i--){
        if(ans[i]){
            continue;
        }
        que[qh=qt=1]=i;
        while(qh<=qt){
            now=que[qh++];
            ans[now]=i;
            for(j=hed[now];j;j=nxt[j]){
                if(ans[to[j]]==0){
                    que[++qt]=to[j];
                }
            }
        }
    }
    for(i=1;i<=n;i++){
        write(ans[i]);
        SP;
    }
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
