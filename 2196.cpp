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
#define N 25
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void Out(int);
int dp[N],last[N];
int a[N];
bool f[N][N];
int main(){
    int n,i,j,ans=0,end;
    read(n);
    for(i=1;i<=n;i++){
        read(a[i]);
    }
    for(i=1;i<=n;i++){
        dp[i]+=a[i];
        for(j=i+1;j<=n;j++){
            read(f[i][j]);
            if(f[i][j]){
                if(dp[i]>dp[j]){
                    last[j]=i;
                    dp[j]=dp[i];
                }
            }
        }
        if(dp[i]>ans){
            end=i;
            ans=dp[i];
        }
    }
    Out(end);
    EL;
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
void Out(int x){
    if(last[x]==0){
        write(x);
        SP;
        return;
    }else{
        Out(last[x]);
        write(x);
        SP;
    }
}
