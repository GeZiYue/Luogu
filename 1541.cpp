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
#define N 350
#define M 45
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int a[N];
int s[6];
int dp[M][M][M][M];
int main () {
    int n , m , i , j , k , l , b;
    read(n);
    read(m);
    for (i = 1 ; i <= n ; i++) {
        read(a[i]);
    }
    for (i = 1 ; i <= m ; i++) {
        read(b);
        s[b]++;
    }
    for (i = 0 ; i <= s[1] ; i++) {
        for (j = 0 ; j <= s[2] ; j++) {
            for (k = 0 ; k <= s[3] ; k++) {
                for (l = 0 ; l <= s[4] ; l++) {
                    dp[i][j][k][l] = max(
                        max(i == 0 ? 0 : dp[i - 1][j][k][l],
                            j == 0 ? 0 : dp[i][j - 1][k][l]),
                        max(k == 0 ? 0 : dp[i][j][k - 1][l],
                            l == 0 ? 0 : dp[i][j][k][l - 1])
                    ) + a[i + 2 * j + 3 * k + 4 * l + 1];
                }
            }
        }
    }
    write(dp[s[1]][s[2]][s[3]][s[4]]);
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
