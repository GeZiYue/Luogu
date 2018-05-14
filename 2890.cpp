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
#define N 2005
#define M 30
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int cost[M],dp[N][N];
string str;
int main(){
    int l,i,j,n,m,a,b;
    char ch;
    read(n);
    read(m);
    cin>>str;
    for(i=1;i<=n;i++){
        cin>>ch;
        read(a);
        read(b);
        cost[ch-'a'+1]=min(a,b);
    }
    for(l=1;l<=m;l++){
        for(i=0;i+l-1<m;i++){
            j=i+l-1;
            if(str[i]==str[j]){
                dp[i][j]=dp[i+1][j-1];
            }else{
                dp[i][j]=min(dp[i][j-1]+cost[str[j]-'a'+1],dp[i+1][j]+cost[str[i]-'a'+1]);
            }
        }
    }
    write(dp[0][m-1]);
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
