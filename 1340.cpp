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
#define N 205
#define M 6005
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int find(int x);
int Kruskal();
int n,id;
int fa[N];
bool use[2*M],del[2*M];
int ans[M];
class Edge{
private:
    int from,to,id,val;
public:
    void add(int x,int y,int z,int n);
    int From();
    int To();
    int Id();
    int Val();
    friend bool operator<(Edge,Edge);
}E[2*M];
int main(){
    int m,i,a,b,c;
    read(n);
    read(m);
    for(i=1;i<=m;i++){
        read(a);
        read(b);
        read(c);
        E[++id].add(a,b,c,i);
        E[++id].add(a,b,c,i);
    }
    sort(E+1,E+id+1);
    memset(ans,-1,sizeof(ans));
    ans[m]=Kruskal();
    for(i=m-1;i>=1;i--){
        del[i+1]=1;
        ans[i]=use[i+1]?Kruskal():ans[i+1];
        if(ans[i]==-1){
            break;
        }
    }
    for(i=1;i<=m;i++){
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
void Edge::add(int x,int y,int z,int n){
    this->from=x;
    this->to=y;
    this->val=z;
    this->id=n;
}
int Edge::From(){
    return this->from;
}
int Edge::To(){
    return this->to;
}
int Edge::Id(){
    return this->id;
}
int Edge::Val(){
    return this->val;
}
bool operator<(Edge x,Edge y){
    return x.Val()<y.Val();
}
int find(int x){
    if(fa[x]==x){
        return x;
    }else{
        return fa[x]=find(fa[x]);
    }
}
int Kruskal(){
    int i,sum=0,num=0;
    int f1,f2;
    memset(use,0,sizeof(use));
    for(i=1;i<=n;i++){
        fa[i]=i;
    }
    for(i=1;i<=id;i++){
        if(del[E[i].Id()]){
            continue;
        }
        f1=find(E[i].From());
        f2=find(E[i].To());
        if(f1!=f2){
            num++;
            sum+=E[i].Val();
            use[E[i].Id()]=1;
            fa[f2]=f1;
        }
        if(num==n-1){
            break;
        }
    }
    if(num==n-1){
        return sum;
    }else{
        return -1;
    }
}
