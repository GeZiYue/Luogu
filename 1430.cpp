#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 1005
#define File(a) freopen(a".in", "r", stdin) , freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int dp[N][N], m1[N][N], m2[N][N];
int sum[N];
int main () {
    int t;
    read(t);
    while (t--) {
        int n;
        read(n);
        for (register int i = 1; i <= n; i++) {
            int a;
            read(a);
            sum[i] = sum[i - 1] + a;
            dp[i][i] = m1[i][i] = m2[i][i] = a;
        }
        for (register int l = 2; l <= n; l++) {
            for (register int i = 1; i + l - 1 <= n; i++) {
                int j = i + l - 1;
                dp[i][j] = sum[j] - sum[i - 1] - min(0, min(m1[i][j - 1], m2[i + 1][j]));
                m1[i][j] = min(dp[i][j], m1[i][j - 1]);
                m2[i][j] = min(dp[i][j], m2[i + 1][j]);
            }
        }
        write(dp[1][n]);
        EL;
    }
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k = 0;
    char ch = getchar();
    int flag = 1;
    while(!isNum(ch) ) {
        if (ch == '-') {
            flag = -1;
        }
        ch = getchar();
    }
    while(isNum(ch) ) {
        k = (k << 1) + (k << 3) + ch - '0';
        ch = getchar();
    }
    r_e_a_d = flag * k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e < 0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e < 10) {
            putchar(w_r_i_t_e + '0');
        }else {
            write(w_r_i_t_e / 10);
            putchar( (w_r_i_t_e % 10) + '0');
        }
    }
}
