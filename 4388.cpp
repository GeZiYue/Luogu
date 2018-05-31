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
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int phi(int);
int main(){
    int i,n,ans=0;
    read(n);
    for(i=1;i*i<=n;i++){
        if(n%i==0){
            if(i*i==n){
                ans+=phi(i+1);
                break;
            }
            ans+=phi(i+1)+phi(n/i+1);
        }
    }
    write((ans+1)>>1);
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
int phi(int x){
    int i,ans=x;
    for(i=2;i*i<=x;i++){
        if(x%i==0){
            while(x%i==0){
                x/=i;
            }
            ans=ans/i*(i-1);
        }
    }
    if(x!=1){
        ans=ans/x*(x-1);
    }
    return ans;
}
