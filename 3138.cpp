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
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int x[N],y[N];
int xx[10]={0,1,1,-1,-1},yy[10]={0,1,-1,1,-1};
int main(){
    int n,i,j,k,a,b,c,d,nx,ny,ans;
    read(n);
    for(i=1;i<=n;i++){
        read(x[i]);
        read(y[i]);
    }
    ans=n;
    for(i=1;i<=n;i++){
        for(j=1;j<=4;j++){
            nx=x[i]+xx[j];
            ny=y[i]+yy[j];
            a=b=c=d=0;
            for(k=1;k<=n;k++){
                if(x[k]<nx&&y[k]<ny){
                    a++;
                }
                if(x[k]<nx&&y[k]>ny){
                    b++;
                }
                if(x[k]>nx&&y[k]<ny){
                    c++;
                }
                if(x[k]>nx&&y[k]>ny){
                    d++;
                }
            }
            ans=min(ans,max(max(a,b),max(c,d)));
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
