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
#define N 1000
#define M 100000
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
double dp[M+5],k[N+5];
int v[N+5];
int main(){
    int n,i,j,l,sum=0,ans=0;
    double m;
    read(n);
    read(l);
    m=(100-l)*1.0/100;
    for(i=1;i<=n;i++){
        read(l);
        k[i]=(100-l)*1.0/100;
        read(v[i]);
        sum+=v[i];
    }
    dp[0]=1;
    for(i=1;i<=n;i++){
        for(j=sum-v[i];j>=0;j--){
            dp[j+v[i]]=max(dp[j+v[i]],dp[j]*k[i]);
            if(dp[j+v[i]]>=m){
                ans=max(ans,j+v[i]);
            }
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
