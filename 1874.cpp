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
#define inf 2147483647
#define N 45
#define M 100005
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
typedef long long int ll;
int dp[N][M];
ll sum[N][N];
string str;
int main(){
    int n,m,i,j,k;
    cin>>str;
    read(m);
    n=str.size();
    memset(sum,-1,sizeof(sum));
    for(i=1;i<=n;i++){
        sum[i][i-1]=0;
        for(j=i;j<=n;j++){
            sum[i][j]=(sum[i][j-1]<<1)+(sum[i][j-1]<<3)+str[j-1]-'0';
            if(sum[i][j]>m){
                break;
            }
        }
    }
    for(i=0;i<=n;i++){
        for(j=0;j<=m;j++){
            dp[i][j]=inf;
        }
    }
    for(i=1;i<=n;i++){
        if(sum[1][i]>m){
            break;
        }
        dp[i][sum[1][i]]=0;
    }
    for(i=2;i<=n;i++){
        for(j=i-1;j>=0;j--){
            if(sum[j+1][i]>m||sum[j+1][i]==-1){
                break;
            }
            for(k=0;k<=m-sum[j+1][i];k++){
                if(dp[j][k]==inf){
                    continue;
                }else{
                    dp[i][k+sum[j+1][i]]=min(dp[i][k+sum[j+1][i]],dp[j][k]+1);
                }
            }
        }
    }
    if(dp[n][m]==inf){
        dp[n][m]=-1;
    }
    write(dp[n][m]);
    EL;
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
