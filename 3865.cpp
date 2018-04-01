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
#define N 100005
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int dp[20][N],l2[N],a[N],p2[20];
int main(){
    int n,m,i,j,x,y,l;
    read(n);
    read(m);
    for(i=1;i<=n;i++){
        read(a[i]);
    }
    l2[0]=-1;
    p2[0]=1;
    for(i=1;i<=n;i++){
        l2[i]=((i&(i-1))==0)?l2[i-1]+1:l2[i-1];
    }
    for(i=1;i<=20;i++){
        p2[i]=p2[i-1]*2;
    }
    for(i=1;i<=n;i++){
        dp[0][i]=a[i];
    }
    for(i=1;i<=l2[n];i++){
        for(j=1;j+p2[i]-1<=n;j++){
            dp[i][j]=max(dp[i-1][j],dp[i-1][j+p2[i-1]]);
        }
    }
    for(i=1;i<=m;i++){
        read(x);
        read(y);
        l=l2[y-x+1];
        write(max(dp[l][x],dp[l][y-p2[l]+1]));
        EL;
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
