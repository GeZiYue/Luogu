#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 1005
#define M 40005
#define Mod 998244353
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int a[N];
int f[N][M];
int* dp[N];
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        read(a[i]);
        dp[i]=f[i]+20001;
    }
    int ans=0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<i; ++j) {
            dp[i][a[i]-a[j]]=(dp[j][a[i]-a[j]]+dp[i][a[i]-a[j]]+1)%Mod;
            ans=(ans+dp[j][a[i]-a[j]]+1)%Mod;
        }
    }
    write((ans+n)%Mod);
    EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while (!isNum(ch)) {
        if (ch=='-') {
            flag=-1;
        }
        ch=getchar();
    }
    while (isNum(ch) ) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d = flag*k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e<0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e<10) {
            putchar(w_r_i_t_e+'0');
        }else {
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
