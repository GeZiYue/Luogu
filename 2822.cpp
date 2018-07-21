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
#define N 2000
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int f[N + 5][N + 5];
int sum[N + 5][N + 5];
int main () {
    int t , Mod , n , m , i , j;
    read(t);
    read(Mod);
    for (i = 1 ; i <= N ; i++) {
        for (j = 1 ; j <= i ; j++) {
            f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % Mod;
            if (j == 1 || j == i) {
                f[i][j] = 1;
            }
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (f[i][j] == 0);
        }
        sum[i][i + 1] = sum[i][i];
    }
    while (t--) {
        read(n);
        n++;
        read(m);
        m++;
        m = min(n , m);
        write(sum[n][m]);
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
