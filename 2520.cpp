#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define ll long long int
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
ll gcd(ll , ll);
bool check(ll , ll);
ll k;
int main () {
    int t;
    read(t);
    while (t--) {
        ll a , b , x , y;
        read(a);
        read(b);
        read(x);
        read(y);
        k = gcd(a , b) * 2;
        if (check(x , y) || check(x + a , y + b) || check(x + b , y + a) || check(x + a + b , y + a + b)) {
            putchar('Y');
        }else {
            putchar('N');
        }
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
ll gcd(ll a , ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b , a % b);
}
bool check(ll x , ll y) {
    return (x % k == 0) && (y % k == 0);
}
