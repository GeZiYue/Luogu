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
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int sum[200005];
int a[55][200005];
int len[55];
int main(){
    int n,m,k,i,j,l,l2,ans=0;
    read(n);
    read(m);
    read(k);
    for(i=1;i<=n;i++){
        read(l);
        read(l2);
        sum[i]=sum[i-1]+(l2<=k);
        a[l+1][++len[l+1]]=i;
    }
    for(i=1;i<=m;i++){
        l=1;
        for(j=1;j<=len[i];j++){
            while(l<j&&sum[a[i][j]]-sum[a[i][l]-1]>0){
                l++;
            }
            l--;
            ans+=l;
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
