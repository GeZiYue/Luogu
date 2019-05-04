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
const int N = 100005, M = 200005;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

void add(int, int, int);
void dfs1(int);
void dfs2(int);

void treebuild(int, int, int);
int treequery(int, int, int, int, int);
void treeupdate(int, int, int, int, int, int);
void treechange(int, int, int, int, int, int);

int query(int, int);
void update(int, int, int);
void change(int, int, int);

int hed[N], nxt[M], to[M], dis[N], id;
int fa[N], dep[N], siz[N], son[N], top[N], tre[N], rnk[N], tim;
int num[N];
int maxn[N << 2], taga[N << 2], tagc[N << 2];
int n;

int main () {
    read(n);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        read(u), read(v), read(w);
        add(u, v, w), add(v, u, w);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    treebuild(1, 1, n);
    while (true) {
        char ch[10];
        std::cin >> ch;
        if (ch[0] == 'S') {
            break;
        }
        if (ch[0] == 'C') {
            if (ch[1] == 'h') {
                int k, w;
                read(k), read(w);
                change(to[(k << 1) - 1], to[k << 1], w);
            } else {
                int u, v, w;
                read(u), read(v), read(w);
                change(u, v, w);
            }
        } else {
            if (ch[0] == 'A') {
                int u, v, w;
                read(u), read(v), read(w);
                update(u, v, w);
            } else {
                int u, v;
                read(u), read(v);
                write(query(u, v)), EL;
            }
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

void add(int u, int v, int w) {
    nxt[++id] = hed[u];
    hed[u] = id;
    to[id] = v;
    dis[id] = w;
}
void dfs1(int u) {
    siz[u] = 1;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa[u]) {
            fa[v] = u;
            dep[v] = dep[u] + 1;
            num[v] = dis[i];
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

void treepushup(int x) {
    maxn[x] = max(maxn[ls(x)], maxn[rs(x)]);
}
void treepushdown(int x) {
    if (~tagc[x]) {
        maxn[ls(x)] = maxn[rs(x)] = tagc[ls(x)] = tagc[rs(x)] = tagc[x];
        taga[ls(x)] = taga[rs(x)] = 0;
        tagc[x] = -1;
    }
    if (taga[x]) {
        maxn[ls(x)] += taga[x];
        maxn[rs(x)] += taga[x];
        taga[ls(x)] += taga[x];
        taga[rs(x)] += taga[x];
        taga[x] = 0;
    }
}
void treebuild(int x, int xL, int xR) {
    tagc[x] = -1;
    if (xL == xR) {
        maxn[x] = num[rnk[xL]];
        return;
    }
    int xM = (xL + xR) >> 1;
    treebuild(ls(x), xL, xM);
    treebuild(rs(x), xM + 1, xR);
    treepushup(x);
}
int treequery(int x, int xL, int xR, int qL, int qR) {
    if (xL >= qL && xR <= qR) {
        return maxn[x];
    }
    if (xR < qL || xL > qR) {
        return -1;
    }
    treepushdown(x);
    int xM = (xL + xR) >> 1;
    return max(treequery(ls(x), xL, xM, qL, qR), treequery(rs(x), xM + 1, xR, qL, qR));
}
void treeupdate(int x, int xL, int xR, int uL, int uR, int num) {
    if (xL >= uL && xR <= uR) {
        maxn[x] += num;
        taga[x] += num;
        return;
    }
    if (xR < uL || xL > uR) {
        return;
    }
    treepushdown(x);
    int xM = (xL + xR) >> 1;
    treeupdate(ls(x), xL, xM, uL, uR, num);
    treeupdate(rs(x), xM + 1, xR, uL, uR, num);
    treepushup(x);
}
void treechange(int x, int xL, int xR, int cL, int cR, int num) {
    if (xL >= cL && xR <= cR) {
        maxn[x] = num;
        taga[x] = 0;
        tagc[x] = num;
        return;
    }
    if (xR  < cL || xL > cR ) {
        return;
    }
    treepushdown(x);
    int xM = (xL + xR) >> 1;
    treechange(ls(x), xL, xM, cL, cR, num);
    treechange(rs(x), xM + 1, xR, cL, cR, num);
    treepushup(x);
}

int query(int x, int y) {
    int ans = 0;
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y ^= x ^= y;
        }
        ans = max(ans, treequery(1, 1, n, tre[top[x]], tre[x]));
        x = fa[top[x]];
    }
    if (x == y) {
        return ans;
    }
    if (dep[x] < dep[y]) {
        x ^= y ^= x ^= y;
    }
    ans = max(ans, treequery(1, 1, n, tre[y] + 1, tre[x]));
    return ans;
}
void update(int x, int y, int num) {
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y ^= x ^= y;
        }
        treeupdate(1, 1, n, tre[top[x]], tre[x], num);
        x = fa[top[x]];
    }
    if (x == y) {
        return;
    }
    if (dep[x] < dep[y]) {
        x ^= y ^= x ^= y;
    }
    treeupdate(1, 1, n, tre[y] + 1, tre[x], num);
}
void change(int x, int y, int num) {
    while (top[x] ^ top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y ^= x ^= y;
        }
        treechange(1, 1, n, tre[top[x]], tre[x], num);
        x = fa[top[x]];
    }
    if (x == y) {
        return;
    }
    if (dep[x] < dep[y]) {
        x ^= y ^= x ^= y;
    }
    treechange(1, 1, n, tre[y] + 1, tre[x], num);
}
