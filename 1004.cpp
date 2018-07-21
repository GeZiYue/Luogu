#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 15
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int dp[N][N][N][N];
int a[N][N];
int main () {
    int n , x , y , w , i , j , k , l;
    read(n);
    while (1) {
        read(x);
        if (x == 0) {
            break;
        }
        read(y);
        read(w);
        a[x][y] = w;
    }
    for (i = 1 ; i <= n ; i++) {
        for (j = 1 ; j <= n ; j++) {
            for (k = 1 ; k <= n ; k++) {
                for (l = 1 ; l <= n ; l++) {
                    dp[i][j][k][l] = max(
                        max(
                            dp[i - 1][j][k - 1][l],
                            dp[i - 1][j][k][l - 1]
                        ),
                        max(
                            dp[i][j - 1][k - 1][l],
                            dp[i][j - 1][k][l - 1]
                        )
                    ) + a[i][j] + a[k][l];
                    if (i == k && j == l) {
                        dp[i][j][k][l] -= a[i][j];
                    }
                }
            }
        }
    }
    write(dp[n][n][n][n]);
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
