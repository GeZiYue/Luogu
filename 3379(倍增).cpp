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
const int N = 500005, M = 1000005;

void add(int, int);
void dfs(int, int);
int lca(int, int);

int hed[N], nxt[M], to[M], id;
int up[N][25], dep[N];

int main () {
    int n, m, root;
    read(n), read(m), read(root);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u), read(v);
        add(u, v), add(v, u);
    }
    dep[root] = 1;
    dfs(root, 0);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        read(a), read(b);
        write(lca(a, b)), EL;
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

void add(int u, int v) {
    nxt[++id] = hed[u];
    hed[u] = id;
    to[id] = v;
}
void dfs(int u, int fa) {
    for (int i = 1; (1 << i) < dep[u]; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v ^ fa) {
            dep[v] = dep[u] + 1;
            up[v][0] = u;
            dfs(v, u);
        }
    }
}
int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        a ^= b ^= a ^= b;
    }
    int k = dep[a] - dep[b];
    for (int i = 0; k; ++i, k >>= 1) {
        if (k & 1) {
            a = up[a][i];
        }
    }
    if (a == b) {
        return a;
    }
    for (int i = 20; i >= 0; --i) {
        if (up[a][i] ^ up[b][i]) {
            a = up[a][i], b = up[b][i];
        }
    }
    return up[a][0];
}
