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
void qadd(int, int, int);
int find(int);
void tarjan(int);

int hed[N], nxt[M], to[M], id;
int qhed[N], qnxt[M], qto[M], qnum[M], qid;
int fa[N];
int vis[N];
int ans[N];

int main () {
    int n, m, root;
    read(n), read(m), read(root);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u), read(v);
        add(u, v), add(v, u);
    }
    for (int i = 1; i <= m; ++i) {
        int u, v;
        read(u), read(v);
        qadd(u, v, i), qadd(v, u, i);
    }
    tarjan(root);
    for (int i = 1; i <= m; ++i) {
        write(ans[i]), EL;
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
void qadd(int u, int v, int num) {
    qnxt[++qid] = qhed[u];
    qhed[u] = qid;
    qto[qid] = v;
    qnum[qid] = num;
}
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void tarjan(int u) {
    fa[u] = u, vis[u] = true;
    for (int i = qhed[u]; i; i = qnxt[i]) {
        int v = qto[i];
        if (vis[v]) {
            ans[qnum[i]] = find(v);
        }
    }
    for (int i = hed[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!vis[v]) {
            tarjan(v);
            fa[v] = u;
        }
    }
}
