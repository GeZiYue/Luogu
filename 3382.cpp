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
#define N 15
#define EPS 1e-6
#define File(a) freopen(a".in", "r", stdin) , freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
double f(double x);
double a[N];
int n;
int main () {
    read(n);
    double L, R;
    cin >> L >> R;
    for (int i = n; i >= 0; i--) {
        cin >> a[i];
    }
    double M1, M2;
    while (R - L >= EPS) {
        M1 = L + (R - L)/3;
        M2 = R - (R - L)/3;
        if (f(M1) > f(M2)) {
            R = M2;
        }else {
            L = M1;
        }
    }
    cout.precision(5);
    cout << fixed << (M1 + M2)/2 << endl;
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
double f(double x) {
    double now = 1, ans = 0;
    for (register int i = 0; i <= n; ++i, now *= x) {
        ans += now * a[i];
    }
    return ans;
}
