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
#define N 55
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int Query(int , int);
int x[N] , w[N] , sum[N];
int dp1[N][N] , dp2[N][N];
int main () {
    int n , begin , i , j , l;
    read(n);
    read(begin);
    memset(dp1 , 127 , sizeof(dp1));
    memset(dp2 , 127 , sizeof(dp2));
    for (i = 1 ; i <= n ; i++) {
        read(x[i]);
        read(w[i]);
        sum[i] = sum[i - 1] + w[i];
    }
    dp1[begin][begin] = 0;
    dp2[begin][begin] = 0;
    for (l = 2 ; l <= n ; l++) {
        for (i = 1 ; i + l - 1 <= n ; i++) {
            j = i + l - 1;
            dp1[i][j] = min(
                dp1[i + 1][j] + (x[i + 1] - x[i]) * (sum[n] - Query(i + 1 , j)),
                dp2[i + 1][j] + (x[j] - x[i]) * (sum[n] - Query(i + 1 , j))
            );
            dp2[i][j] = min(
                dp2[i][j - 1] + (x[j] - x[j - 1]) * (sum[n] - Query(i , j - 1)),
                dp1[i][j - 1] + (x[j] - x[i]) * (sum[n] - Query(i , j - 1))
            );
        }
    }
    write(min(dp1[1][n] , dp2[1][n]));
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
int Query(int x, int y) {
    return sum[y] - sum[x - 1];
}
