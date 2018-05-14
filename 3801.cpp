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
#define ll long long int
#define N 100000
#define ls(x) (x<<1)
#define rs(x) (ls(x)|1)
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
class Tree{
private:
    int sum[4*N+5];
public:
    int Query(int,int,int,int,int);
    void Update(int,int,int,int,int);
}x,y;
int main(){
    int n,m,q,i,x1,x2,y1,y2,a,nx,ny;
    ll ans;
    read(n);
    read(m);
    read(q);
    for(i=1;i<=q;i++){
        read(a);
        if(a==1){
            read(x1);
            read(y1);
            x.Update(1,1,n,x1,x1);
            y.Update(1,1,m,y1,y1);
        }else{
            read(x1);
            read(y1);
            read(x2);
            read(y2);
            nx=x.Query(1,1,n,x1,x2);
            ny=y.Query(1,1,m,y1,y2);
            ans=(ll)(nx)*(ll)(y2-y1+1)+(ll)(ny)*(ll)(x2-x1+1)-(ll)(nx)*(ll)(ny)*2;
            write(ans);
            EL;
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
int Tree::Query(int x,int xL,int xR,int qL,int qR){
    if(xL>=qL&&xR<=qR){
        return sum[x];
    }
    if(xR<qL||xL>qR){
        return 0;
    }
    int xM=(xL+xR)>>1;
    return Query(ls(x),xL,xM,qL,qR)+Query(rs(x),xM+1,xR,qL,qR);
}
void Tree::Update(int x,int xL,int xR,int uL,int uR){
    if(xR<uL||xL>uR){
        return;
    }
    if(xL==xR){
        sum[x]^=1;
        return;
    }
    int xM=(xL+xR)>>1;
    Update(ls(x),xL,xM,uL,uR);
    Update(rs(x),xM+1,xR,uL,uR);
    sum[x]=sum[ls(x)]+sum[rs(x)];
}
