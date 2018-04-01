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
#define M 100005
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int find(int x);
void merge(int x,int y);
int fa[N],ans;
struct R{
    int x,y,t;
}a[M];
int main(){
    int n,m,i;
    read(n);
    read(m);
    ans=n;
    for(i=1;i<=n;i++){
        fa[i]=i;
    }
    for(i=1;i<=m;i++){
        read(a[i].x);
        read(a[i].y);
        read(a[i].t);
    }
    sort(a+1,a+m+1,[](R x,R y){
        return x.t<y.t;
    });
    for(i=1;i<=m;i++){
        merge(a[i].x,a[i].y);
        if(ans==1){
            write(a[i].t);
            EL;
            break;
        }
    }
    if(ans>1){
        write(-1);
    }
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
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx^fy){
        fa[fy]=fx;
        ans--;
    }
}
