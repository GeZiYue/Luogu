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

typedef long long ll;
typedef const long long & cll;
typedef const int & ci;
const int N = 205;
const int Mod1 = 1019663265;
const int Mod2 = 1000003;
const int mod[] = {3, 5, 6793, 10007, 1000003};

int pow(ci, int, ci);
int Lucas(ci, ci, ci);
int sum(ci, ci, ci);

int a[N], b[N];
int f[N][N];
int fac[5][1000010], inv[5][1000010];
int invmod[4];

int main () {
    for (int i = 0; i < 5; ++i) {
        if (i < 4) {
            invmod[i] = pow(Mod1 / mod[i], mod[i] - 2, mod[i]);
        }
        fac[i][0] = fac[i][1] = inv[i][0] = inv[i][1] = 1;
        for (int j = 2; j <= mod[i]; ++j) {
            fac[i][j] = fac[i][j - 1] * 1ll * j % mod[i];
            inv[i][j] = (mod[i] - mod[i] / j) * 1ll * inv[i][mod[i] % j] % mod[i];
        }
        for (int j = 2; j <= mod[i]; ++j) {
            inv[i][j] = inv[i][j - 1] * 1ll *inv[i][j] % mod[i];
        }
    }
    int n, m, t, p;
    read(n), read(m), read(t), read(p);
    for (int i = 1; i <= t; ++i) {
        read(a[i]), read(b[i]);
    }
    a[t + 1] = n, b[t + 1] = m;
    int ans = sum(0, t + 1, p);
    std::cout << ans << '\n';
    for (int i = 1; i <= t; ++i) {
        f[1][i] = sum(0, i, p);
        ans = (ans - f[1][i] * 1ll * sum(i, t + 1, p) % p + p) % p;
    }
    for (int i = 2; i <= t; ++i) {
        int mod = (i & 1) ? -1 : 1;
        for (int j = 1; j <= t; ++j) {
            for (int k = 1; k <= t; ++k) {
                if (j == k) {
                    continue;
                }
                std::cout << i << ' ' << j << ' ' << k << '\n';
                if (a[k] <= a[j] && b[k] <= b[j]) {
                    f[i][j] = (f[i][j] + f[i - 1][k] * 1ll * sum(k, j, p) % p) % p;
                }
            }
            ans = (ans + mod * f[i][j] * 1ll * sum(i, t + 1, p) % p + p) % p;
        }
    }
    write(ans), EL;
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
int lucas(ci n, ci m, ci d) {
    if (n < m) {
        return 0;
    }
    if (n == 0 || n == m) {
        return 1;
    }
    const int p = mod[d];
    if (n <= p && m <= p) {
        return fac[d][n] * 1ll * inv[d][m] % p * inv[d][n - m] % p;
    }
    return lucas(n / p, m / p, d) * lucas(n % p, m % p, d) % p;
}
int CRT(ci c, ci d) {
    return c * 1ll * invmod[d] % Mod1 * (Mod1 / mod[d]) % Mod1;
}
int Lucas(ci n, ci m, ci p) {
    if (p == Mod1) {
        int ans = 0;
        for (int i = 0; i < 4; ++i) {
            ans = (ans + CRT(lucas(n, m, i), i)) % p;
        }
        return (ans % p + p) % p;
    } else {
        return lucas(n, m, 4);
    }
}
int sum(ci i, ci j, ci p) {
    return Lucas(abs(a[i] - a[j]) + abs(b[i] - b[j]), abs(a[i] - a[j]), p);
}
