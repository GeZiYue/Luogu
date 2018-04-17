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
#define M 200005
#define turnzero(a) memset(a,0,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void add(int,int,int);
void DFS(int);
bool flag[N];
bool ans;
int hed[N],nxt[M<<1],to[M<<1],v[M<<1],id;
int dis[N];
int main(){
    int t,n,m,i,x,y,w;
    read(t);
    while(t--){
        read(n);
        read(m);
        turnzero(hed);
        turnzero(dis);
        turnzero(flag);
        ans=false;
        id=0;
        for(i=1;i<=m;i++){
            read(x);
            read(y);
            read(w);
            add(x,y,w);
            if(w>=0){
                add(y,x,w);
            }
        }
        for(i=1;i<=n&&ans==false;i++){
            flag[i]=true;
            DFS(i);
            flag[i]=false;
        }
        if(ans){
            puts("YE5");
        }else{
            puts("N0");
        }
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
void add(int x,int y,int w){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    v[id]=w;
}
void DFS(int x){
    int i;
    for(i=hed[x];i;i=nxt[i]){
        if(ans){
            break;
        }
        if(dis[x]+v[i]<dis[to[i]]){
            if(flag[to[i]]){
                ans=true;
                break;
            }
            dis[to[i]]=dis[x]+v[i];
            flag[to[i]]=true;
            DFS(to[i]);
            flag[to[i]]=false;
        }
    }
}
