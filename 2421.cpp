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
const int N = 15;
const int M = 1000000;

bool check(int);

int c[N], p[N], l[N];
int n;

int main () {
    read(n);
    int maxc = 0;
    for (int i = 1; i <= n; ++i) {
        read(c[i]), read(p[i]), read(l[i]);
        maxc = max(maxc, c[i]);
    }
    for (int i = maxc; i <= M; ++i) {
        if (check(i)) {
            write(i), EL;
            return 0;
        }
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

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int t = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return t;
}
bool check(int m) {
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int v = p[i] - p[j];
            int s = c[j] - c[i];
            if (v < 0) {
                v = -v, s = -s;
            }
            int x, y;
            int k = exgcd(v, m, x, y);
            x = (x + m) % m;
            if (s % k == 0) {
                x = (x * (s / k) % (m / k) + (m / k)) % (m / k);
                if (x <= l[i] && x <= l[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}
