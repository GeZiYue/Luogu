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
#define N 20005
#define M 100005
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int find(int x);
void merge(int x,int y,int d);
struct Node{
    int x,y,d;
}a[M];
int fa[N],k[N];
int ans;
int main(){
    int n,m,i;
    read(n);
    read(m);
    for(i=1;i<=n;i++){
        fa[i]=i;
    }
    memset(k,-1,sizeof(k));
    for(i=1;i<=m;i++){
        read(a[i].x);
        read(a[i].y);
        read(a[i].d);
    }
    sort(a+1,a+m+1,[](Node x,Node y){
        return x.d>y.d;
    });
    for(i=1;i<=m;i++){
        merge(a[i].x,a[i].y,a[i].d);
    }
    write(0);
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
int find(int x){
    if(fa[x]==x){
        return x;
    }else{
        return fa[x]=find(fa[x]);
    }
}
void merge(int x,int y,int d){
    if(find(x)==find(y)){
        write(d);
        EL;
        exit(0);
    }else{
        if(k[x]==-1){
            k[x]=y;
        }else{
            fa[find(k[x])]=find(y);
        }
        if(k[y]==-1){
            k[y]=x;
        }else{
            fa[find(k[y])]=find(x);
        }
    }
}
