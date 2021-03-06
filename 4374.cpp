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
const int N = 50005, M = 100005;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

void add(int, int);
void dfs1(int);
void dfs2(int);

void segtreeupdate(int, int, int, int, int, int);
void update(int, int, int);

void getans(int, int, int);

int hed[N], nxt[M], to[M], id = 1;
int dep[N], fa[N], siz[N], son[N], num[N];
int top[N], tre[N], rnk[N], tim;
int minn[N << 2], tag[N << 2];
int ans[N];
int n;

int main () {
    int m;
    read(n), read(m);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u), read(v);
        add(u, v), add(v, u);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    for (int i = 1; i <= n << 2; ++i) {
        tag[i] = minn[i] = iinf;
    }
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        read(u), read(v), read(w);
        update(u, v, w);
    }
    getans(1, 1, n);
    for (int i = 1; i < n; ++i) {
        write(ans[i] == iinf ? -1 : ans[i]), EL;
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
        if (v != fa[u]) {
            dep[v] = dep[u] + 1;
            fa[v] = u;
            num[v] = i >> 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) {
                son[u] = v;
            }
        }
    }
}
void dfs2(int u) {
    tre[u] = ++tim;
    rnk[tim] = u;
    if (son[u]) {
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != son[u] && v != fa[u]) {
            top[v] = v;
            dfs2(v);
        }
    }
}

void pushdown(int x) {
    if (tag[x] != iinf) {
        minn[ls(x)] = min(minn[ls(x)], tag[x]);
        minn[rs(x)] = min(minn[rs(x)], tag[x]);
        tag[ls(x)] = min(tag[ls(x)], tag[x]);
        tag[rs(x)] = min(tag[rs(x)], tag[x]);
        tag[x] = iinf;
    }
}
void pushup(int x) {
    minn[x] = min(minn[ls(x)], minn[rs(x)]);
}
void segtreeupdate(int x, int xL, int xR, int uL, int uR, int u) {
    if (xL >= uL && xR <= uR) {
        minn[x] = min(minn[x], u);
        tag[x] = min(tag[x], u);
        return;
    }
    if (xL > uR || xR < uL) {
        return;
    }
    pushdown(x);
    int xM = (xL + xR) >> 1;
    segtreeupdate(ls(x), xL, xM, uL, uR, u), segtreeupdate(rs(x), xM + 1, xR, uL, uR, u);
    pushup(x);
}
void update(int x, int y, int u) {
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y ^= x ^= y;
        }
        segtreeupdate(1, 1, n, tre[top[x]], tre[x], u);
        x = fa[top[x]];
    }
    if (x == y) {
        return;
    }
    if (dep[x] < dep[y]) {
        x ^= y ^= x ^= y;
    }
    segtreeupdate(1, 1, n, tre[son[y]], tre[x], u);
}
void getans(int x, int xL, int xR) {
    if (xL == xR) {
        ans[num[rnk[xL]]] = minn[x];
        return;
    }
    pushdown(x);
    int xM = (xL + xR) >> 1;
    getans(ls(x), xL, xM), getans(rs(x), xM + 1, xR);
}
