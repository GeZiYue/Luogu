#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 25
#define M 2000005
#define Mod 998244353
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
char ch[N];
int dp[N];
int c[N][N];
int main () {
    int n;
    int m;
    read(n);
    read(m);
    c[0][0]=1;
    for (int i=1; i<=n; ++i) {
        c[i][0]=1;
        for (int j=1; j<=i; ++j) {
            c[i][j]=c[i-1][j-1]+c[i-1][j];
        }
    }
    dp[0]=1;
    for (int i=1; i<=n; ++i) {
        for (int j=0; j<i; ++j) {
            dp[i]=(dp[i]+dp[j]*1ll*c[i][j]%Mod)%Mod;
        }
    }
    int ans=0;
    for (int i=1; i<=m; ++i) {
        int cnt=0;
        int k;
        scanf("%s", ch+1);
        for (int j=1; j<=n; ++j) {
            if (ch[j]-'0') {
                ++cnt;
            }
        }
        read(k);
        ans=(ans+k*1ll%Mod*dp[cnt]%Mod*dp[n-cnt]%Mod)%Mod;
    }
    write(ans);
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
