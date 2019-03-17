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

int phi(int);
int pow(int, int, int);

int main () {
    int a, m, b = 0;
    read(a), read(m);
    int k = phi(m);
    char ch = getchar();
    bool flag = false;
    while (isNum(ch)) {
        b = (b << 1) + (b << 3) + ch - '0';
        if (b > k) {
            flag = true;
            b %= k;
        }
        ch = getchar();
    }
    if (flag) {
        b += k;
    }
    write(pow(a, b, m)), EL;
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

int phi(int x) {
    int k = x;
    int ans = x;
    for (int i = 2; i * i <= x; ++i) {
        if (k % i == 0) {
            while (k % i == 0) {
                k /= i;
            }
            ans -= ans / i;
        }
    }
    if (k ^ 1) {
        ans -= ans / k;
    }
    return ans;
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
