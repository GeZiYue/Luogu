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
#define N 20005
#define inf 1000000000
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
bool f[N];
int a[105];
int dp[N];
int main () {
    int n , m , s , t , i , j , now = 0;
    read(m);
    read(s);
    read(t);
    read(n);
    for (i = 1 ; i <= n ; i++){
        read(a[i]);
    }
    if (s == t) {
        int ans = 0;
        for (i = 1 ; i <= n ; i++) {
            if (a[i] % s == 0) {
                ans++;
            }
        }
        write(ans);
        EL;
        return 0;
    }
    sort(a + 1 , a + n + 1);
    for (i = 1 ; i <= n ; i++) {
        if (a[i] - a[i - 1] > t) {
            now += (a[i] - a[i - 1]) % t + t;
        }else {
            now += a[i] - a[i - 1];
        }
        f[now] = true;
    }
    now += t;
    for (i = 1 ; i <= now ; i++) {
        dp[i] = inf;
        for (j = s ; j <= min(t , i) ; j++) {
            dp[i] = min(dp[i] , dp[i - j] + f[i]);
        }
    }
    write(dp[now]);
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
