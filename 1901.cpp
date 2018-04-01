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
#define ll long long int
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int sta[N],h[N],v[N];
ll ans[N];
int main(){
    int s,i,n;
    ll maxn=0;
    read(n);
    for(i=1;i<=n;i++){
        read(h[i]);
        read(v[i]);
    }
    sta[s=1]=1;
    for(i=2;i<=n;i++){
        while(s&&h[i]>=h[sta[s]]){
            ans[i]+=v[sta[s]];
            s--;
        }
        sta[++s]=i;
    }
    sta[s=1]=n;
    for(i=n-1;i>=1;i--){
        while(s&&h[i]>=h[sta[s]]){
            ans[i]+=v[sta[s]];
            s--;
        }
        sta[++s]=i;
    }
    for(i=1;i<=n;i++){
        maxn=max(maxn,ans[i]);
    }
    write(maxn);
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
