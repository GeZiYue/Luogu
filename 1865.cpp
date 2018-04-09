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
#define N 1000005
#define M 1000005
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
void Get_Prime(int n);
int prime[M],id=0;
int sum[N];
bool flag[N];
int main(){
    int n,m,i,x,y;
    read(n);
    read(m);
    Get_Prime(m);
    for(i=1;i<=n;i++){
        read(x);
        read(y);
        if(y>m||x<1){
            puts("Crossing the line");
            continue;
        }
        write(sum[y]-sum[x-1]);
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
void Get_Prime(int n){
    int i,j;
    for(i=2;i<=n;i++){
        sum[i]=sum[i-1];
        if(flag[i]==false){
            prime[++id]=i;
            sum[i]++;
        }
        for(j=1;j<=id&&i*prime[j]<=n;j++){
            flag[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}
