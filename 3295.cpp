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
const int N = 100005;
const int M = 25;
const int Mod = 1000000007;

int find(int, int);
void merge(int, int, int);

int lg2[N];
int fa[N][M];

int main () {
    int n, m;
    read(n), read(m);
    for (int i = 2; i <= n; ++i) {
        lg2[i] = lg2[i >> 1] + 1;
    }
    for (int i = 0; i <= lg2[n]; ++i) {
        for (int j = 1; j <= n - (1 << i) + 1; ++j) {
            fa[j][i] = j;
        }
    }
    for (int i = 1; i <= m; ++i) {
        int l1, r1, l2, r2;
        read(l1), read(r1), read(l2), read(r2);
        int k = lg2[r1 - l1 + 1];
        merge(k, l1, l2);
        merge(k, r1 - (1 << k) + 1, r2 - (1 << k) + 1);
    }
    for (int i = lg2[n]; i >= 1; --i) {
        for (int j = 1; j <= n - (1 << i) + 1; ++j) {
            int f = find(i, j);
            merge(i - 1, f, j);
            merge(i - 1, f + (1 << (i  - 1)), j + (1 << (i - 1)));
        }
    }
    bool flag = true;
    int ans = 1;
    for (int i = 1; i <= n; ++i) {
        if (find(0, i) == i) {
            if (flag) {
                ans = ans * 1ll * 9 % Mod;
                flag = false;
            } else {
                ans = ans * 1ll * 10 % Mod;
            }
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

int find(int k, int x) {
    return fa[x][k] == x ? x : fa[x][k] = find(k, fa[x][k]);
}
void merge(int k, int x, int y) {
    int fx = find(k, x), fy = find(k, y);
    if (fx ^ fy) {
        fa[fy][k] = fx;
    }
}
