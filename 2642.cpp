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
#define N 1000005
#define inf 2147483647
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
typedef long long int ll;
int a[N];
ll dp1[N] , dp2[N];
int main () {
    int n , i;
    ll now , ans;
    read(n);
    for (i = 1 ; i <= n ; i++) {
        read(a[i]);
    }
    dp1[0] = -inf;
    now = 0;
    for (i = 1 ; i < n ; i++) {
        now += a[i];
        dp1[i] = max(dp1[i - 1] , now);
        if (now < 0) {
            now = 0;
        }
    }
    dp2[n + 1] = -inf;
    now = 0;
    for (i = n ; i > 1 ; i--) {
        now += a[i];
        dp2[i] = max(dp2[i + 1] , now);
        if (now < 0) {
            now = 0;
        }
    }
    ans = -inf;
    for (i = 1 ; i < n - 1 ; i++) {
        ans = max(ans , dp1[i] + dp2[i + 2]);
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
