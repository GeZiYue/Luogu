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
#define N 105
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
class Node {
public:
    friend bool operator < (Node , Node);
    int t , f , h;
}a[N];
int dp[N][N];
int main () {
    int n , m , i , j;
    read(m);
    read(n);
    for (i = 1 ; i <= n ; i++) {
        read(a[i].t);
        read(a[i].f);
        read(a[i].h);
    }
    sort(a + 1 , a + n + 1);
    memset(dp , -1 , sizeof(dp));
    dp[0][0] = 10;
    for (i = 1 ; i <= n ; i++) {
        for (j = 0 ; j <= m ; j++) {
            if (dp[i - 1][j] < a[i].t - a[i - 1].t) {
                continue;
            }
            if (j + a[i].h >= m) {
                write(a[i].t);
                EL;
                return 0;
            }
            dp[i][j + a[i].h] = max(dp[i][j + a[i].h] , dp[i - 1][j] - a[i].t + a[i - 1].t);
            dp[i][j] = max(dp[i][j] , dp[i - 1][j] + a[i].f - a[i].t + a[i - 1].t);
        }
    }
    int ans = 0;
    for (i = 1 ; i <= n ; i++) {
        if (dp[i][0] >= 0) {
            ans = max(ans , dp[i][0] + a[i].t);
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
bool operator < (Node i , Node j) {
    return i.t < j.t;
}
