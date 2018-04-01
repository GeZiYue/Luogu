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
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int find(int x);
void merge(int x,int y);
void Add_Friend(int x,int y);
void Add_Enemy(int x,int y);
int f[N],e[N];
int ans;
int main(){
    int n,m,i,a,b;
    char ch;
    read(n);
    read(m);
    ans=n;
    for(i=1;i<=n;i++){
        f[i]=i;
    }
    for(i=1;i<=m;i++){
        cin>>ch;
        read(a);
        read(b);
        if(ch=='F'){
            Add_Friend(a,b);
        }else{
            Add_Enemy(a,b);
        }
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
    if(f[x]==x){
        return x;
    }else{
        return f[x]=find(f[x]);
    }
}
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx^fy){
        f[fy]=fx;
        ans--;
    }
}
void Add_Friend(int x,int y){
    merge(x,y);
}
void Add_Enemy(int x,int y){
    if(e[x]==0){
        e[x]=y;
    }else{
        merge(e[x],y);
    }
    if(e[y]==0){
        e[y]=x;
    }else{
        merge(e[y],x);
    }
}
