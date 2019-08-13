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
const int M = 200005;
const int K = 300005;
const int L = 25;

class Edge {
public:
    int u, v, val;
    bool operator < (const Edge &i) const {
        return val < i.val;
    }
}e[K];

int find(int);
void add(int, int, int);
void dfs(int);
int query(int, int);

int fa[N];
int hed[N], nxt[M], to[M], val[M], id;
int dep[N], up[N][L], maxv[N][L];

int main () {
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= m; ++i) {
        read(e[i].u), read(e[i].v), read(e[i].val);
    }
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        if (find(e[i].u) ^ find(e[i].v)) {
            fa[fa[e[i].v]] = fa[e[i].u];
            add(e[i].u, e[i].v, e[i].val);
            add(e[i].v, e[i].u, e[i].val);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!dep[i]) {
            dep[i] = 1;
            dfs(i);
        }
    }
    int q;
    read(q);
    for (int i = 1; i <= q; ++i) {
        int x, y;
        read(x), read(y);
        int ans = query(x, y);
        if (ans == -1) {
            puts("impossible");
        } else {
            write(ans), EL;
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

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void add(int u, int v, int dis) {
    nxt[++id] = hed[u];
    hed[u] = id;
    to[id] = v;
    val[id] = dis;
}
void dfs(int u) {
    for (int i = 1; (1 << i) < dep[u]; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        maxv[u][i] = max(maxv[u][i - 1], maxv[up[u][i - 1]][i - 1]);
    }
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v ^ up[u][0]) {
            dep[v] = dep[u] + 1;
            up[v][0] = u;
            maxv[v][0] = val[i];
            dfs(v);
        }
    }
}
int query(int x, int y) {
    if (find(x) ^ find(y)) {
        return -1;
    }
    if (dep[x] < dep[y]) {
        x ^= y ^= x ^= y;
    }
    int ans = 0;
    for (int i = dep[x] - dep[y], j = 0; i; i >>= 1, ++j) {
        if (i & 1) {
            ans = max(ans, maxv[x][j]);
            x = up[x][j];
        }
    }
    if (x == y) {
        return ans;
    }
    for (int i = 20; i >= 0; --i) {
        if (up[x][i] ^ up[y][i]) {
            ans = max(ans, maxv[x][i]);
            ans = max(ans, maxv[y][i]);
            x = up[x][i];
            y = up[y][i];
        }
    }
    ans = max(ans, maxv[x][0]);
    ans = max(ans, maxv[y][0]);
    return ans;
}
