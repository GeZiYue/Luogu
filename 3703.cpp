#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

const int N = 100005;
const int M = 200005;

class Node {
 public:
  int fa, ch[2];
  int le;
};
Node tre[N];
#define fa(x) (tre[x].fa)
#define lc(x) (tre[x].ch[0])
#define rc(x) (tre[x].ch[1])
#define le(x) (tre[x].le)
int sta[N];

void access(int x);
int count(int x);
void add(int u, int v);
void dfs1(int u);
void dfs2(int u);
int lca(int u, int v);
void update(int x, int num);
int query(int x);

int hed[N], nxt[M], to[M], id;
int dfn[N], siz[N], fa[N], dep[N], son[N], top[N], cnt;
int maxi[N << 2], tag[N << 2];
int n, q;

int main() {
  read(n), read(q);
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  dfs1(1);
  top[1] = 1;
  dfs2(1);
  while (q--) {
    int op;
    read(op);
    if (op == 1) {
      int u;
      read(u);
      access(u);
    } else {
      if (op == 2) {
        int u, v;
        read(u), read(v);
        write(count(u) + count(v) - 2 * count(lca(u, v)) + 1), EL;
      } else {
        int u;
        read(u);
        write(query(u)), EL;
      }
    }
  }
  return 0;
}

template <class T>
inline void read(T &Re) {
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
template <class T>
inline void write(const T &Wr) {
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

void pushdown(int x) {
  if (tag[x]) {
    maxi[x << 1] += tag[x];
    maxi[x << 1 | 1] += tag[x];
    tag[x << 1] += tag[x];
    tag[x << 1 | 1] += tag[x];
    tag[x] = 0;
  }
}
void update(int x, int xl, int xr, int ul, int ur, int num) {
  if (ul <= xl && xr <= ur) {
    maxi[x] += num;
    tag[x] += num;
    return;
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    update(x << 1, xl, xm, ul, ur, num);
  }
  if (ur > xm) {
    update(x << 1 | 1, xm + 1, xr, ul, ur, num);
  }
  maxi[x] = max(maxi[x << 1], maxi[x << 1 | 1]);
}
int query(int x, int xl, int xr, int ql, int qr) {
  if (ql <= xl && xr <= qr) {
    return maxi[x];
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  int ans = 0;
  if (ql <= xm) {
    ans = max(ans, query(x << 1, xl, xm, ql, qr));
  }
  if (qr > xm) {
    ans = max(ans, query(x << 1 | 1, xm + 1, xr, ql, qr));
  }
  return ans;
}
bool nroot(int x) { return lc(fa(x)) == x || rc(fa(x)) == x; }
bool getid(int x) { return rc(fa(x)) == x; }
void pushup(int x) { le(x) = lc(x) ? le(lc(x)) : x; }
void rotate(int x) {
  int y = fa(x), z = fa(y), yid = getid(x), zid = getid(y), w = tre[x].ch[yid ^ 1];
  if (nroot(y)) {
    tre[z].ch[zid] = x;
  }
  tre[x].ch[yid ^ 1] = y;
  tre[y].ch[yid] = w;
  if (w) {
    fa(w) = y;
  }
  fa(x) = z;
  fa(y) = x;
  pushup(y);
}
void splay(int x) {
  int y = x;
  while (nroot(x)) {
    y = fa(x);
    if (nroot(y)) {
      rotate(getid(x) == getid(y) ? y : x);
    }
    rotate(x);
  }
  pushup(x);
}
int findlas(int x) {
  while (true) {
    if (lc(x)) {
      x = lc(x);
    } else {
      return x;
    }
  }
}
void access(int x) {
  for (int y = 0; x; x = fa(y = x)) {
    splay(x);
    if (rc(x)) {
      update(le(rc(x)), 1);
    }
    rc(x) = y;
    pushup(x);
    if (y) {
      update(le(y), -1);
    }
  }
}
int findroot(int x) {
  splay(x);
  while (true) {
    if (lc(x)) {
      x = lc(x);
    } else {
      splay(x);
      return x;
    }
  }
}
int count(int x) { return query(1, 1, n, dfn[x], dfn[x]); }
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs1(int u) {
  dfn[u] = ++cnt;
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa[u]) {
      continue;
    }
    fa(v) = u;
    fa[v] = u;
    dep[v] = dep[u] + 1;
    dfs1(v);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
  update(u, 1);
}
void dfs2(int u) {
  if (son[u]) {
    top[son[u]] = top[u];
    dfs2(son[u]);
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa[u] && v != son[u]) {
      top[v] = v;
      dfs2(v);
    }
  }
}
int lca(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] > dep[top[v]]) {
      u = fa[top[u]];
    } else {
      v = fa[top[v]];
    }
  }
  return dep[u] < dep[v] ? u : v;
}
void update(int x, int num) { update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, num); }
int query(int x) { return query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1); }
