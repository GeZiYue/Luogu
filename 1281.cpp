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
#define N 505
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
void print(int);
int dp[N][N];
int sum[N];
int ans;
int main () {
    int n , m , i , j , k , a;
    read(n);
    read(m);
    for (i = 1 ; i <= n ; i++) {
        read(a);
        sum[i] = sum[i - 1] + a;
    }
    for (i = 1 ; i <= n ; i++) {
        for (j = 1 ; j <= i && j <= m ; j++) {
            dp[i][j] = 2147483647;
            if (j == 1) {
                dp[i][j] = sum[i];
                continue;
            }
            for (k = 0 ; k < i ; k++) {
                dp[i][j] = min(dp[i][j] , max(dp[k][j - 1] , sum[i] - sum[k]));
            }
        }
    }
    ans = dp[n][m];
    print(n);
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
void print(int begin) {
    if (begin == 0) {
        return;
    }
    int i , now = 0;
    for (i = begin ; i >= 0 ; i--) {
        now += sum[i] - sum[i - 1];
        if (now > ans || i == 0) {
            print(i);
            write(i + 1);
            SP;
            write(begin);
            EL;
            break;
        }
    }
}
