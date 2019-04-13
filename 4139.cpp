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
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 10000005;

int phi[N];
bool isPrime[N];
int Prime[N], id;

void getphi(int);
int pow(int, int);
int Get(int);

int main () {
    getphi(N - 5);
    int t;
    read(t);
    while (t--) {
        int x;
        read(x);
        write(Get(x)), EL;
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

void getphi(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!isPrime[i]) {
            phi[i] = i - 1;
            Prime[++id] = i;
        }
        for (int j = 1; j <= id && Prime[j] * i <= n; ++j) {
            isPrime[i * Prime[j]] = true;
            if (i % Prime[j] == 0) {
                phi[i * Prime[j]] = phi[i] * Prime[j];
            } else {
                phi[i * Prime[j]] = phi[i] * (Prime[j] - 1);
            }
        }
    }
}
int pow(int a, int b, int mod) {
    int now = a % mod, ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * 1ll * now % mod;
        }
        now = now * 1ll * now % mod;
        b >>= 1;
    }
    return ans;
}
int Get(int x) {
    if (x == 1) {
        return 0;
    }
    return pow(2, Get(phi[x]) + phi[x], x);
}
