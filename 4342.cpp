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
#define inf 2147483647
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int a[N],dp1[N][N],dp2[N][N];
bool b[N];
int main(){
    int n,i,j,k,l,ans=0;
    int l1,l2,l3,l4;
    char ch;
    read(n);
    for(i=1;i<=n;i++){
        cin>>ch;
        if(ch=='t'){
            b[i]=true;
        }
        read(a[i]);
        b[i+n]=b[i];
        dp1[i][i]=dp2[i][i]=a[i];
        dp1[i+n][i+n]=dp2[i+n][i+n]=a[i];
    }
    for(l=2;l<=n;l++){
        for(i=1;i<=(n<<1)-l+1;i++){
            j=i+l-1;
            dp1[i][j]=-inf;
            dp2[i][j]=inf;
            for(k=i+1;k<=j;k++){
                l1=dp1[i][k-1];
                l2=dp2[i][k-1];
                l3=dp1[k][j];
                l4=dp2[k][j];
                if(b[k]){
                    dp1[i][j]=max(dp1[i][j],l1+l3);
                    dp2[i][j]=min(dp2[i][j],l2+l4);
                }else{
                    dp1[i][j]=max(dp1[i][j],max(max(l1*l3,l1*l4),max(l2*l3,l2*l4)));
                    dp2[i][j]=min(dp2[i][j],min(min(l1*l3,l1*l4),min(l2*l3,l2*l4)));
                }
            }
        }
    }
    for(i=1;i<=n;i++){
        ans=max(ans,dp1[i][i+n-1]);
    }
    write(ans);
    EL;
    for(i=1;i<=n;i++){
        if(dp1[i][i+n-1]==ans){
            write(i);
            SP;
        }
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
