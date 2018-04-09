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
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int dp[2][N][N];
bool go[N][N];
int main(){
    int n,m,t,i,j,k;
    int n2,m2,n3,m3;
    int x1,x2,y1,y2;
    char ch;
    read(n);
    read(m);
    read(t);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            cin>>ch;
            if(ch=='*'){
                go[i][j]=true;
            }
        }
    }
    read(x1);
    read(y1)
    read(x2);
    read(y2);
    dp[0][x1][y1]=1;
    n2=min(n,max(x1,x2)+t);
    m2=min(m,max(y1,y2)+t);
    n3=max(1,min(x1,x2)-t);
    m3=max(1,min(y1,y2)-t);
    for(i=1;i<=t;i++){
        for(j=n3;j<=n2;j++){
            for(k=m3;k<=m2;k++){
                if(go[j][k]){
                    continue;
                }
                dp[i&1][j][k]=dp[(i&1)^1][j-1][k]+dp[(i&1)^1][j+1][k]+dp[(i&1)^1][j][k-1]+dp[(i&1)^1][j][k+1];
            }
        }
    }
    write(dp[t&1][x2][y2]);
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
