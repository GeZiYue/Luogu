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
const int N = 100005;
const int M = 200005;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

void add(int, int);
void dfs1(int);
void dfs2(int);
void update(int, int, int);
inline ll query(int);

int hed[N], nxt[M], to[M], id;
int dep[N], fa[N], son[N], siz[N], top[N], ttl[N], ltt[N], dfn;
ll sum[N << 2];
int tag[N << 2];
int n;

int main () {
    read(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u), read(v);
        ++u, ++v;
        add(u, v);
        add(v, u);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    int m;
    read(m);
    for (int i = 1; i <= m; ++i) {
        char ch = getchar();
        while (ch != 'A' && ch != 'Q') {
            ch = getchar();
        }
        if (ch == 'A') {
            int x, y, num;
            read(x), read(y), read(num);
            ++x, ++y;
            update(x, y, num);
        } else {
            int x;
            read(x);
            ++x;
            write(query(x)), EL;
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
    ttl[u] = ++dfn;
    ltt[dfn] = u;
    if (son[u]) {
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = to[i];
        if ((v ^ fa[u]) && (v ^ son[u])) {
            top[v] = v;
            dfs2(v);
        }
    }
}
inline ll uni(ll l, ll r) {
    return l + r;
}
inline void pushdown(int x, int xl, int xr) {
    if (tag[x]) {
        tag[ls(x)] += tag[x];
        tag[rs(x)] += tag[x];
        int xm = (xl + xr) >> 1;
        sum[ls(x)] += (xm - xl + 1) * 1ll * tag[x];
        sum[rs(x)] += (xr - xm) * 1ll * tag[x];
        tag[x] = 0;
    }
}
void update(int x, int xl, int xr, int ul, int ur, int num) {
    if (xl > ur || xr < ul) {
        return;
    }
    if (xl >= ul && xr <= ur) {
        tag[x] += num;
        sum[x] += (xr - xl + 1) * 1ll * num;
        return;
    }
    pushdown(x, xl, xr);
    int xm = (xl + xr) >> 1;
    update(ls(x), xl, xm, ul, ur, num);
    update(rs(x), xm + 1, xr, ul, ur, num);
    sum[x] = uni(sum[ls(x)], sum[rs(x)]);
}
ll query(int x, int xl, int xr, int ql, int qr) {
    if (xl > qr || xr < ql) {
        return 0;
    }
    if (xl >= ql && xr <= qr) {
        return sum[x];
    }
    pushdown(x, xl, xr);
    int xm = (xl + xr) >> 1;
    return uni(
        query(ls(x), xl, xm, ql, qr),
        query(rs(x), xm + 1, xr, ql, qr)
    );
}
void update(int x, int y, int num) {
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y ^= x ^= y;
        }
        update(1, 1, n, ttl[top[x]], ttl[x], num);
        x = fa[top[x]];
    }
    if (dep[x] < dep[y]) {
        x ^= y ^= x ^= y;
    }
    update(1, 1, n, ttl[y], ttl[x], num);
}
ll query(int x) {
    return query(1, 1, n, ttl[x], ttl[x] + siz[x] - 1);
}
