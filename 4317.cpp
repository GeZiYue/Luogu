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
const int N = 65;
const int Mod = 10000007;

ll pow(ll, ll);
ll get(int);

ll f[N][N];
bool num[N];
int id;

int main () {
    ll n;
    read(n);
    ll now = n + 1;
    while (now) {
        num[++id] = now & 1;
        now >>= 1;
    }
    for (int i = 0; i <= id; ++i) {
        f[i][0] = 1;
    }
    for (int i = 1; i <= id; ++i) {
        for (int j = 1; j <= i; ++j) {
            f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
        }
    }
    ll ans = 1;
    for (int i = 1; i <= id; ++i) {
        ans = ans * pow(i, get(i)) % Mod;
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

ll pow(ll a, ll b) {
    int ans = 1, now = a % Mod;
    while (b) {
        if (b & 1) {
            ans = ans * 1ll * now % Mod;
        }
        now = now * 1ll * now % Mod;
        b >>= 1;
    }
    return ans;
}
ll get(int x) {
    ll ans = 0;
    for (int i = id; i >= 1; --i) {
        if (num[i]) {
            ans = ans + f[i - 1][x--];
        }
        if (x < 0) {
            break;
        }
    }
    return ans;
}
