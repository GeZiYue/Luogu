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
#define N 55
#define inf 2147483647
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
char a[N];
int dp[N][N];
int main () {
    int n;
    cin >> (a + 1);
    n = strlen(a + 1);
    for (int i = 1 ; i <= n ; i++) {
        dp[i][i] = 1;
    }
    for (int l = 2 ; l <= n ; l++) {
        for (int i = 1 ; i + l - 1 <= n ; i++) {
            int j = i + l - 1;
            if (a[i] == a[j]) {
                dp[i][j] = min(dp[i + 1][j] , dp[i][j - 1]);
            }else {
                dp[i][j] = inf;
                for (int k = i ; k < j ; k++) {
                    dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }
    write(dp[1][n]);
    EL;
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
