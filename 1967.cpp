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
const int N = 10005, M = 50005;

class Edge {
public:
    int u, v, w;
    bool operator< (const Edge& i) const {
        return w > i.w;
    }
}e[M];

int find(int);
void add(int, int, int);
void dfs(int);
int query(int, int);

int fa[N];
int hed[N], nxt[N << 1], to[N << 1], dis[N << 1], id;
int dep[N], up[N][20], mind[N][20];

int main () {
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= m; ++i) {
        read(e[i].u), read(e[i].v), read(e[i].w);
    }
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        if (find(e[i].u) != find(e[i].v)) {
            add(e[i].u, e[i].v, e[i].w);
            add(e[i].v, e[i].u, e[i].w);
            fa[fa[e[i].v]] = fa[e[i].u];
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (dep[i] == 0) {
            dep[i] = 1;
            dfs(i);
        }
    }
    int q;
    read(q);
    for (int i = 1; i <= q; ++i) {
        int x, y;
        read(x), read(y);
        write(query(x, y)), EL;
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
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void add(int u, int v, int w) {
    nxt[++id] = hed[u];
    hed[u] = id;
    to[id] = v;
    dis[id] = w;
}
void dfs(int u) {
    for (int i = 1; (1 << i) < dep[u]; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        mind[u][i] = min(mind[u][i - 1], mind[up[u][i - 1]][i - 1]);
    }
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != up[u][0]) {
            dep[v] = dep[u] + 1;
            up[v][0] = u;
            mind[v][0] = dis[i];
            dfs(v);
        }
    }
}
int query(int x, int y) {
    if (find(x) != find(y)) {
        return -1;
    }
    int ans = iinf;
    if (dep[x] < dep[y]) {
        x ^= y ^= x ^= y;
    }
    int k = dep[x] - dep[y];
    for (int i = 0; k; ++i, k >>= 1) {
        if (k & 1) {
            ans = min(ans, mind[x][i]);
            x = up[x][i];
        }
    }
    if (x == y) {
        return ans;
    }
    for (int i = 15; i >= 0; --i) {
        if (up[x][i] != up[y][i]) {
            ans = min(ans, mind[x][i]);
            ans = min(ans, mind[y][i]);
            x = up[x][i];
            y = up[y][i];
        }
    }
    ans = min(ans, mind[x][0]);
    ans = min(ans, mind[y][0]);
    return ans;
}
