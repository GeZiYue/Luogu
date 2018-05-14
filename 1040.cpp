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
#define N 35
#define inf 2147483647
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void Out(int,int);
long long int dp[N][N];
int root[N][N];
int main(){
    int n,i,j,k,l;
    read(n);
    for(i=1;i<=n;i++){
        read(dp[i][i]);
    }
    for(i=1;i<=n+1;i++){
        dp[i][i-1]=1;
    }
    for(l=2;l<=n;l++){
        for(i=1;(i+l-1)<=n;i++){
            j=i+l-1;
            for(k=i;k<=j;k++){
                if(dp[i][j]<dp[i][k-1]*dp[k+1][j]+dp[k][k]){
                    dp[i][j]=dp[i][k-1]*dp[k+1][j]+dp[k][k];
                    root[i][j]=k;
                }
            }
        }
    }
    write(dp[1][n]);
    EL;
    Out(1,n);
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
void Out(int L,int R){
    if(L>R){
        return;
    }
    if(L==R){
        write(L);
        SP;
        return;
    }
    write(root[L][R]);
    SP;
    Out(L,root[L][R]-1);
    Out(root[L][R]+1,R);
}
