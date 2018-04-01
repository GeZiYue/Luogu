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
#define N 400005
#define M 200005
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int x,int y);
int find(int x);
void merge(int x,int y);
int fa[N];
int ans[N],now;
int hed[N],nxt[2*M],to[2*M],id;
bool flag[N];
int a[N];
int main(){
    int n,m,k,i,j,x,y,l;
    read(n);
    read(m);
    for(i=1;i<=n;i++){
        fa[i]=i;
        flag[i]=true;
    }
    now=n;
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        x++;
        y++;
        add(x,y);
        add(y,x);
        merge(x,y);
    }
    write(now);
    EL;
    for(i=1;i<=n;i++){
        fa[i]=i;
    }
    now=n;
    read(k);
    for(i=1;i<=k;i++){
        read(l);
        l++;
        a[i]=l;
        flag[l]=false;
        now--;
    }
    for(i=1;i<=n;i++){
        if(flag[i]){
            for(j=hed[i];j;j=nxt[j]){
                if(flag[to[j]]){
                    merge(i,to[j]);
                }
            }
        }
    }
    for(i=k;i>=1;i--){
        ans[i]=now;
        now++;
        flag[a[i]]=true;
        for(j=hed[a[i]];j;j=nxt[j]){
            if(flag[to[j]]){
                merge(a[i],to[j]);
            }
        }
    }
    for(i=1;i<=k;i++){
        write(ans[i]);
        EL;
    }
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
int find(int x){
    if(fa[x]==x){
        return x;
    }else{
        return fa[x]=find(fa[x]);
    }
}
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx^fy){
        now--;
        fa[fx]=fy;
    }
}
void add(int x,int y){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
}
