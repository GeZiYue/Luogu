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
#define Mod 1000000007ll
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
ll pow(ll , ll);
ll f[N][3];
int main () {
    ll n , k;
    ll i , j;
    read(n);
    read(k);
    if (k == 0) {
        write(pow(n , Mod - 2));
        EL;
        return 0;
    }
    f[3][1] = 1;
    f[3][0] = 0;
    for (i = 4 ; i <= n - k + 1 ; i++) {
        f[i][1] = f[i - 1][1];
        f[i][0] = f[i - 1][0];
    }
    for (i = n - k + 2 ; i <= n ; i++) {
        f[i][1] = ((i - 3) * f[i - 1][1] % Mod + f[i - 1][0]) % Mod * pow(i - 2 , Mod - 2) % Mod;
        f[i][0] = f[i - 1][1];
    }
    write((f[n][1] * (n - 1) % Mod + f[n][0]) * pow(n , Mod - 2) % Mod);
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
ll pow(ll x , ll k) {
    ll ans = 1 , now = x;
    while (k) {
        if (k & 1) {
            ans = ans * now % Mod;
        }
        now = now * now % Mod;
        k >>= 1;
    }
    return ans;
}
