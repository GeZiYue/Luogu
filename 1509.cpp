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
#define N 105
#define M 105
#define inf 2147483647
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int Time[N],RP[N],Money[N];
int dp1[M][M],dp2[M][M];
int main(){
    int n,money,rp,i,j,k;
    int maxn=-inf,minn=inf;
    read(n);
    for(i=1;i<=n;i++){
        read(Money[i]);
        read(RP[i]);
        read(Time[i]);
    }
    read(money);
    read(rp);
    for(i=1;i<=n;i++){
        for(j=money;j>=Money[i];j--){
            for(k=rp;k>=RP[i];k--){
                if(dp1[j][k]==dp1[j-Money[i]][k-RP[i]]+1){
                    dp2[j][k]=min(dp2[j][k],dp2[j-Money[i]][k-RP[i]]+Time[i]);
                }else{
                    if(dp1[j][k]<dp1[j-Money[i]][k-RP[i]]+1){
                        dp1[j][k]=dp1[j-Money[i]][k-RP[i]]+1;
                        dp2[j][k]=dp2[j-Money[i]][k-RP[i]]+Time[i];
                    }
                }
                if(dp1[j][k]==maxn){
                    minn=min(minn,dp2[j][k]);
                }else{
                    if(dp1[j][k]>maxn){
                        maxn=dp1[j][k];
                        minn=dp2[j][k];
                    }
                }
            }
        }
    }
    write(minn);
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
