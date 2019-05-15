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
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
const int N = 100005, M = 200005;

void add(int, int);
void dfs1(int);
void dfs2(int);
int treequery(int, int, int, int, int);
void treeupdate(int, int, int, int);
int query(int, int);

int hed[N], nxt[M], to[M], id;
int fa[N], dep[N], siz[N], son[N], top[N], num[N], rnk[N], tim;
int fir[N << 2], tag[N << 2];
int n;

int main () {
    int q;
    read(n),
    read(q);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u),
        read(v);
        add(u, v),
        add(v, u);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    for (int i = 1; i <= (N << 2) - 10; ++i) {
        fir[i] = iinf;
    }
    for (int i = 1; i <= q; ++i) {
        int mod, x;
        read(mod),
        read(x);
        if (mod) {
            write(query(1, x)), EL;
        } else {
            treeupdate(1, 1, n, num[x]);
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
    num[u] = ++tim;
    rnk[tim] = u;
    if (son[u]) {
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    for (int i = hed[u]; i ; i = nxt[i]) {
        int v = to[i];
        if (v != son[u] && v != fa[u]) {
            top[v] = v;
            dfs2(v);
        }
    }
}
void pushup(int x) {
    fir[x] = min(fir[ls(x)], fir[rs(x)]);
}
int treequery(int x, int xl, int xr, int ql, int qr) {
    if (xl >= ql && xr <= qr) {
        return fir[x];
    }
    if (xl > qr || xr < ql) {
        return iinf;
    }
    int xm = (xl + xr) >> 1;
    return min(
        treequery(ls(x), xl, xm, ql, qr),
        treequery(rs(x), xm + 1, xr, ql, qr)
    );
}
void treeupdate(int x, int xl, int xr, int ux) {
    if (xl > ux || xr < ux) {
        return;
    }
    if (xl == xr) {
        if (fir[x] == iinf) {
            fir[x] = xl;
        } else {
            fir[x] = iinf;
        }
        return;
    }
    int xm = (xl + xr) >> 1;
    treeupdate(ls(x), xl, xm, ux),
    treeupdate(rs(x), xm + 1, xr, ux);
    pushup(x);
}
int query(int x, int y) {
    int ans = iinf;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y ^= x ^= y;
        }
        ans = min(ans, treequery(1, 1, n, num[top[x]], num[x]));
        x = fa[top[x]];
    }
    if (dep[x] < dep[y]) {
        x ^= y ^= x ^= y;
    }
    ans = min(ans, treequery(1, 1, n, num[y], num[x]));
    return ans == iinf ? -1 : rnk[ans];
}
