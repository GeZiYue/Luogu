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
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
inline void read(T&);
template<class T>
inline void write(const T&);

typedef long long ll;
typedef unsigned long long ull;
typedef const int& ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;

ll pow(ll, ll, ll);

int main () {
    ll k, l, p, s, w;
    read(k), read(l), read(p), read(s), read(w);
    k %= p;
    if (!s) {
        if (l == 1) {
            write(k), EL;
        }
        write(k * ((k - 1 + p) % p) % p * pow((k - 2 + p) % p, l - 2, p) % p), EL;
    } else {
        if (l == 1) {
            write(1), EL;
        }
        write((k - 1 + p) % p * pow((k - 2 + p) % p, l - 2, p) % p), EL;
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

ll pow(ll a, ll n, ll mod) {
    ll ans = 1, now = a;
    while (n) {
        if (n & 1) {
            ans = ans * now % mod;
        }
        now = now * now % mod;
        n >>= 1;
    }
    return ans;
}
