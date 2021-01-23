#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 500005;
constexpr int Mod = 998244353;

void inc(int &a, int b);
void dec(int &a, int b);

namespace Seg_Tree {
class Node {
 public:
  int lc, rc;
  int tagm, taga;
} tre[N * 130];
int rot[N];
int tot;
void add(int &x, int num);
void mul(int &x, int num);
void pushdown(int x);
void update_add(int &x, int xl, int xr, int ul, int ur, int num);
void update_mul(int &x, int xl, int xr, int ul, int ur, int num);
int query(int x, int xl, int xr, int qx);
int merge(int x, int y, int xl, int xr);
}  // namespace Seg_Tree

void add(int u, int v);
void dfs1(int u, int fa);
void dfs2(int u, int fa);

int hed[N], nxt[N << 1], to[N << 1], id;
int dep[N], pre[N];
int n, m;

int main() {
  read(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  dfs1(1, 0);
  int m;
  read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    pre[v] = std::max(pre[v], dep[u] + 1);
  }
  dfs2(1, 0);
  using namespace Seg_Tree;
  write(query(rot[1], 0, n, 0)), EL;
  return 0;
}

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs1(int u, int fa) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    dep[v] = dep[u] + 1;
    dfs1(v, u);
  }
}
void dfs2(int u, int fa) {
  using namespace Seg_Tree;
  pre[u] = std::max(pre[u], pre[fa]);
  update_add(rot[u], 0, n, pre[u], dep[u], 1);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    dfs2(v, u);
    rot[u] = merge(rot[u], rot[v], 0, n);
  }
  if (u != 1) {
    int now = query(rot[u], 0, n, dep[u]);
    update_add(rot[u], 0, n, 0, dep[u] - 1, now);
  }
}

void inc(int &a, int b) { (a += b) >= Mod ? a -= Mod : a; }
void dec(int &a, int b) { (a -= b) < 0 ? a += Mod : a; }
void mlt(int &a, int b) { a = 1ll * a * b % Mod; }
namespace Seg_Tree {
void add(int &x, int num) {
  if (!x) {
    x = ++tot;
    tre[x].taga = 0, tre[x].tagm = 1;
  }
  inc(tre[x].taga, num);
}
void mul(int &x, int num) {
  if (!x) {
    x = ++tot;
    tre[x].taga = 0, tre[x].tagm = 1;
  }
  mlt(tre[x].taga, num);
  mlt(tre[x].tagm, num);
}
void pushdown(int x) {
  if (tre[x].tagm != 1) {
    mul(tre[x].lc, tre[x].tagm);
    mul(tre[x].rc, tre[x].tagm);
    tre[x].tagm = 1;
  }
  if (tre[x].taga) {
    add(tre[x].lc, tre[x].taga);
    add(tre[x].rc, tre[x].taga);
    tre[x].taga = 0;
  }
}
void update_add(int &x, int xl, int xr, int ul, int ur, int num) {
  if (!x) {
    x = ++tot;
    tre[x].taga = 0, tre[x].tagm = 1;
  }
  if (ul <= xl && xr <= ur) {
    add(x, num);
    return;
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    update_add(tre[x].lc, xl, xm, ul, ur, num);
  }
  if (ur > xm) {
    update_add(tre[x].rc, xm + 1, xr, ul, ur, num);
  }
}
void update_mul(int &x, int xl, int xr, int ul, int ur, int num) {
  if (!x) {
    x = ++tot;
    tre[x].taga = 0, tre[x].tagm = 1;
  }
  if (ul <= xl && xr <= ur) {
    mul(x, num);
    return;
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    update_mul(tre[x].lc, xl, xm, ul, ur, num);
  }
  if (ur > xm) {
    update_mul(tre[x].rc, xm + 1, xr, ul, ur, num);
  }
}
int query(int x, int xl, int xr, int qx) {
  if (!x) {
    return 0;
  }
  if (xl == xr) {
    return tre[x].taga;
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  if (qx <= xm) {
    return query(tre[x].lc, xl, xm, qx);
  } else {
    return query(tre[x].rc, xm + 1, xr, qx);
  }
}
int merge(int x, int y, int xl, int xr) {
  if (!tre[x].lc && !tre[x].rc) {
    std::swap(x, y);
  }
  if (!tre[y].lc && !tre[y].rc) {
    mul(x, tre[y].taga);
    return x;
  }
  pushdown(x), pushdown(y);
  int xm = (xl + xr) >> 1;
  tre[x].lc = merge(tre[x].lc, tre[y].lc, xl, xm);
  tre[x].rc = merge(tre[x].rc, tre[y].rc, xm + 1, xr);
  return x;
}
}  // namespace Seg_Tree

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
