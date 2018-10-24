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
#define N 55
#define M 2505
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int c[N][N];
int dp[N][M];
int sum[N];
char str[N];
int main () {
    int n, m, t;
    read(n);
    read(m);
    read(t);
    for (int i=1; i<=n; ++i) {
        cin>>(str+1);
        for (int j=1; j<=m; ++j) {
            sum[j]=sum[j-1]+(str[j]=='1');
        }
        memset(c, 0, sizeof(c));
        for (int j=1; j<=m; ++j) {
            for (int k=1; k<=min(m, t); ++k) {
                for (int l=1; l<=j; ++l) {
                    int now=sum[j]-sum[l-1];
                    c[j][k]=max(c[j][k], c[l-1][k-1]+max(now, (j-l+1)-now));
                }
            }
        }
        for (int j=0; j<=t; ++j) {
            for (int k=0; k<=min(j, m); ++k) {
                dp[i][j]=max(dp[i][j], dp[i-1][j-k]+c[m][k]);
            }
        }
    }
    int ans=0;
    for (int i=0; i<=t; ++i) {
        ans=max(ans, dp[n][i]);
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
