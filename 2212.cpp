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
#define N 2005
#define M 4000005
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
class Edge{
public:
    int u,v,dis;
    friend bool operator<(Edge ,Edge );
}e[M];
int cul(int ,int ,int ,int );
void add(int ,int ,int );
int find(int );
bool check(int ,int );
void merge(int ,int );
int x[N],y[N];
int fa[N];
int id;
int main(){
    int n,c,i,j,now,ans=0;
    read(n);
    read(c);
    for(i=1;i<=n;i++){
        read(x[i]);
        read(y[i]);
        fa[i]=i;
        for(j=1;j<i;j++){
            now=cul(x[i],y[i],x[j],y[j]);
            if(now>=c){
                add(i,j,now);
            }
        }
    }
    sort(e+1,e+id+1);
    now=0;
    for(i=1;i<=id;i++){
        if(check(e[i].u,e[i].v)==false){
            now++;
            ans+=e[i].dis;
            merge(e[i].u,e[i].v);
        }
        if(now==(n-1)){
            break;
        }
    }
    if(now!=(n-1)){
        puts("-1");
        return 0;
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
int cul(int x1,int y1,int x2,int y2){
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
void add(int x,int y,int diss){
    e[++id].u=x;
    e[id].v=y;
    e[id].dis=diss;
}
bool operator<(Edge i,Edge j){
    return i.dis<j.dis;
}
int find(int x){
    if(fa[x]==x){
        return x;
    }else{
        return fa[x]=find(fa[x]);
    }
}
bool check(int x,int y){
    int fx=find(x),fy=find(y);
    return fx==fy;
}
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        fa[fy]=fx;
    }
}
