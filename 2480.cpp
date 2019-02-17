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

const int Mod = 999911658;
const int mod[] = {2, 3, 4679, 35617};
const int N = 5;
typedef long long ll;
typedef const long long& cll;
typedef const int& ci;

int fac[N][40000];
int inv[N][40000];
int invmod[N];

int pow(ci, int, ci);
int GetAns(ci, ci);

int main () {
    for (int i = 0; i < 4; ++i) {
        invmod[i] = pow(Mod / mod[i], mod[i] - 2, mod[i]);
        fac[i][0] = fac[i][1] = inv[i][0] = inv[i][1] = 1;
        for (int j = 2; j < mod[i]; ++j) {
            fac[i][j] = fac[i][j - 1] * j % mod[i];
            inv[i][j] = (mod[i] - mod[i] / j) * inv[i][mod[i] % j] % mod[i];
        }
        for (int j = 2; j < mod[i]; ++j) {
            inv[i][j] = inv[i][j - 1] * inv[i][j] % mod[i];
        }
    }
    int n, g;
    read(n), read(g);
    if (g % (Mod + 1) == 0) {
        write(0), EL;
        return 0;
    }
    int ind = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            ind = (ind + GetAns(n, i)) % Mod;
            if (i * i != n) {
                ind = (ind + GetAns(n, n / i)) % Mod;
            }
        }
    }
    write(pow(g, ind, Mod + 1)), EL;
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

int pow(ci a, int b, ci p) {
    int ans = 1, now = a;
    while (b) {
        if (b & 1) {
            ans = ans * 1ll * now % p;
        }
        now = now * 1ll * now % p;
        b >>= 1;
    }
    return ans;
}
int lucas(ci n, ci m, ci p) {
    if (n < m) {
        return 0;
    }
    if (n == 0 || n == m) {
        return 1;
    }
    if (n < mod[p] && m < mod[p]) {
        return fac[p][n] * inv[p][m] % mod[p] * inv[p][n - m] % mod[p];
    }
    return lucas(n / mod[p], m / mod[p], p) * lucas(n % mod[p], m % mod[p], p) % mod[p];
}
int CRT(int c, int d) {
    return c * 1ll * (Mod / mod[d]) % Mod * invmod[d] % Mod;
}
int GetAns(ci n, ci m) {
    ll ans = 0;
    for (int i = 0; i < 4; ++i) {
        ans = (ans + CRT(lucas(n, m, i), i)) % Mod;
    }
    return (ans % Mod + Mod) % Mod;
}
