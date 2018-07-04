#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 65
#define M 32005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int a[N][5] , num[N];
int dp[N][M];
int v[N];
int w[N];
int main () {
    int n , m , i , j , k , ans = 0 , now , p;
    read(m);
    read(n);
    for (i = 1 ; i <= n ; i++) {
        read(v[i]);
        read(w[i]);
        w[i] *= v[i];
        read(p);
        if (p != 0) {
            num[i] = -1;
            a[p][++num[p]] = i;
        }
    }
    for (i = 1 ; i <= n ; i++) {
        if (num[i] == -1) {
            for (j = 1 ; j <= m ; j++) {
                dp[i][j] = dp[i - 1][j];
            }
            continue;
        }
        for (j = m ; j >= v[i] ; j--) {
            dp[i][j] = dp[i - 1][j - v[i]] + w[i];
            ans = max(ans , dp[i][j]);
        }
        for (j = 1 ; j <= num[i] ; j++) {
            now = a[i][j];
            for (k = m ; k >= v[now] + v[i]; k--) {
                dp[i][k] = max(dp[i][k] , dp[i][k - v[now]] + w[now]);
                ans = max(ans , dp[i][k]);
            }
        }
        for (j = 1 ; j <= m ; j++) {
            dp[i][j] = max(dp[i][j] , dp[i - 1][j]);
        }
    }
    write(ans);
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
