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
#define ll long long int
#define N 100005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
int Begin(int);
int End(int);
int New(int);
ll f[30][30] , g[30][30];
char str[N];
ll n , k;
ll sum[N][30];
int main () {
    ll m , T , i , j , l , c , ans = 0;
    ll L , R;
    char x , y;
    read(n);
    read(m);
    read(k);
    read(T);
    cin >> (str + 1);
    for (i = 1 ; i <= 26 ; i++) {
        for (j = 1 ; j <= 26 ; j++) {
            f[i][j] = T;
            if (i == j) {
                f[i][j] = 0;
            }
        }
    }
    for (i = 1 ; i <= m ; i++) {
        cin >> x >> y;
        read(c);
        f[x - 'a' + 1][y - 'a' + 1] = min(f[x - 'a' + 1][y - 'a' + 1] , c);
    }
    for (i = 1 ; i <= 26 ; i++) {
        for (j = 1 ; j <= 26 ; j++) {
            for (l = 1 ; l <= 26 ; l++) {
                f[j][l] = min (f[j][l] , f[j][i] + f[i][l]);
                g[j][l] = f[j][l];
            }
        }
    }
    for (i = 1 ; i <= 26 ; i++) {
        for (j = 1 ; j <= 26 ; j++) {
            for (l = 1 ; l <= 26 ; l++) {
                g[j][l] = min (g[j][l] , f[j][i] + f[l][i]);
            }
        }
    }
    for (i = 1 ; i <= n ; i++) {
        sum[New(i)][str[i] - 'a' + 1] = 1;
    }
    for (i = 1 ; i <= n ; i++) {
        for (j = 1 ; j <= 26 ; j++) {
            sum[i][j] += sum[i - 1][j];
        }
    }
    for (i = 1 ; i <= n ; i++) {
        L = New(Begin(i));
        R = New(End(i));
        for (j = 1 ; j <= 26 ; j++) {
            ans += (sum[R][j] - sum[L - 1][j]) * max(g[str[i] - 'a' + 1][j] , g[j][str[i] - 'a' + 1]);
        }
    }
    write(ans / 2);
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
int Begin(int x) {
    return abs(k - x) + 1;
}
int End(int x) {
    if (x <= n - k + 1) {
        return x + k - 1;
    }else {
        return (n << 1) - (x + k - 1);
    }
}
int New(int x) {
    if (x & 1) {
        return (x + 1) >> 1;
    }else {
        return ((n + 1) >> 1) + (x >> 1);
    }
}
