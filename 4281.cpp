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
const int N = 500005;
const int M = 1000005;

int hed[N], nxt[M], to[M], id;
int fa[N], dep[N], siz[N], son[N], top[N];

void add(int, int);
void dfs1(int);
void dfs2(int);
int lca(int, int);

int main () {
    int n, m;
    read(n), read(m);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u), read(v);
        add(u, v), add(v, u);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        read(a), read(b), read(c);
        int la = lca(a, b), lb = lca(b, c), lc = lca(c, a);
        int ans;
        if (la == lb) {
            ans = lc;
        } else {
            if (la == lc) {
                ans = lb;
            } else {
                ans = la;
            }
        }
        write(ans), SP, write(dep[a] + dep[b] + dep[c] - dep[la] - dep[lb] - dep[lc]), EL;
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
void dfs1(int u) {
    siz[u] = 1;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v ^ fa[u]) {
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) {
                son[u] = v;
            }
        }
    }
}
void dfs2(int u) {
    if (son[u]) {
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    for (int i = hed[u]; i ; i = nxt[i]) {
        int v = to[i];
        if (v ^ son[u] && v ^ fa[u]) {
            top[v] = v;
            dfs2(v);
        }
    }
}
int lca(int x, int y) {
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y ^= x ^= y;
        }
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
