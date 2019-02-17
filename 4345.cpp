#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define inf 2147483647
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
inline void read(T&);
template<class T>
inline void write(const T&);

typedef long long int ll;
typedef const long long int& cll;
const int p = 2333, N = 2334;

int lucas(cll, cll);
int calc(cll, cll);
int c[p + 5][p + 5];
int f[p + 5][p + 5];

int main () {
    c[0][0] = 1;
    for (int i = 1; i <= N; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            c[i][j]=(c[i - 1][j] + c[i - 1][j - 1]) % p;
        }
    }
    for (int i = 0; i <= N; ++i) {
        f[i][0] = 1;
        for (int j = 1; j <= N; ++j) {
            f[i][j]=(f[i][j - 1] + c[i][j]) % p;
        }
    }
    int t;
    read(t);
    while (t--) {
        ll n, k;
        read(n), read(k);
        write(calc(n, k)), EL;
    }
    return 0;
}

template<class T>
void read(T &Re) {
    T k = 0;
    char ch = getchar();
    int flag = 1;
    while (!isNum(ch)) {
        if (ch == '-') {
            flag = -1;
        }
        ch = getchar();
    }
    while (isNum(ch)) {
        k = (k << 1) + (k << 3) + ch - '0';
        ch = getchar();
    }
    Re = flag * k;
}
template<class T>
void write(const T &Wr) {
    if (Wr < 0) {
        putchar('-');
        write(-Wr);
    } else {
        if (Wr < 10) {
            putchar(Wr + '0');
        } else {
            write(Wr / 10);
            putchar((Wr % 10) + '0');
        }
    }
}

int lucas(cll n, cll m) {
    if (!m || n == m) {
        return 1;
    }
    if (n < m) {
        return 0;
    }
    return c[n % p][m % p] * lucas(n / p, m / p) % p;
}
int calc(cll n, cll k) {
    if (k < 0) {
        return 0;
    }
    if (!n || !k) {
        return 1;
    }
    if (n < p && k < p) {
        return f[n][k];
    }
    return (calc(n % p, p - 1) * calc(n / p, k / p - 1) % p + lucas(n / p, k / p) * calc(n % p, k % p) % p) % p;
}
