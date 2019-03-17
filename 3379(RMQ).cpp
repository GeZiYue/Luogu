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
void dfs(int);

int hed[N], nxt[M], to[M], id;
int dep[N];
int fir[N], tot;
int lg2[M];
int p2[22];
int st[M][22], num[M][22];

int main () {
    int n, m, root;
    read(n), read(m), read(root);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u), read(v);
        add(u, v), add(v, u);
    }
    dep[root] = 1;
    dfs(root);
    lg2[1] = 0;
    for (int i = 2; i <= tot; ++i) {
        lg2[i] = lg2[i - 1] + ((i & (i-1)) == 0);
    }
    p2[0] = 1;
    for (int i = 1; i <= lg2[tot]; ++i) {
        p2[i] = p2[i - 1] << 1;
    }
    for (int l = 1; l <= lg2[tot]; ++l) {
        for (int i = 1; i <= tot - p2[l] + 1; ++i) {
            if (st[i][l - 1] < st[i + p2[l - 1]][l - 1]) {
                st[i][l] = st[i][l - 1], num[i][l] = num[i][l - 1];
            } else {
                st[i][l] = st[i + p2[l - 1]][l - 1], num[i][l] = num[i + p2[l - 1]][l - 1];
            }
        }
    }
    for (int i = 1;i <= m; ++i) {
        int a, b;
        read(a), read(b);
        int fa = fir[a], fb = fir[b];
        if (fa > fb) {
            fa ^= fb ^= fa ^= fb;
        }
        int k = lg2[fb - fa + 1];
        if (st[fa][k] < st[fb - p2[k] + 1][k]) {
            write(num[fa][k]), EL;
        } else {
            write(num[fb - p2[k] + 1][k]), EL;
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
void dfs(int u) {
    fir[u] = ++tot, st[tot][0] = dep[u], num[tot][0] = u;
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!fir[v]) {
            dep[v] = dep[u] + 1;
            dfs(v);
            st[++tot][0] = dep[u], num[tot][0] = u;
        }
    }
}
