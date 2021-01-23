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

constexpr int N = 100005;
constexpr int M = 200005;

namespace Tree {
int hed[N], nxt[M], to[M], id;
int dep[N], fa[N];
int ttl[N], ltt[N], tot;
std::vector<pii> Q[N];
void add(int u, int v);
void dfs1(int u);
void dfs2(int u);
}  // namespace Tree
namespace LCA {
int fir[N];
int dfn[M], tot;
int lg2[M];
int stmin[19][M];
int dmin(int u, int v);
void init();
int lca(int u, int v);
}  // namespace LCA
namespace SegT {
class Node {
 public:
  int lc, rc;
  int lp, rp, len, la;
  int sum;
} tre[N * 40];
int tot;
int rot[N];
void pushup(int x);
void update(int &x, int xl, int xr, int ux, int num);
int merge(int x, int y, int xl, int xr);
}  // namespace SegT

int qu[N], qv[N];
ll ans;
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    Tree::add(u, v);
    Tree::add(v, u);
  }
  Tree::dep[1] = 1;
  Tree::dfs1(1);
  LCA::init();
  for (int i = 1; i <= m; ++i) {
    read(qu[i]), read(qv[i]);
    int la = LCA::lca(qu[i], qv[i]);
    Tree::Q[qu[i]].emplace_back(i, 1);
    Tree::Q[qv[i]].emplace_back(i, 1);
    Tree::Q[la].emplace_back(i, -1);
    Tree::Q[Tree::fa[la]].emplace_back(i, -1);
  }
  Tree::dfs2(1);
  write(ans / 2), EL;
  return 0;
}

namespace Tree {
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs1(int u) {
  LCA::dfn[LCA::fir[u] = ++LCA::tot] = u;
  ttl[u] = ++tot;
  ltt[tot] = u;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa[u]) {
      continue;
    }
    dep[v] = dep[u] + 1;
    fa[v] = u;
    dfs1(v);
    LCA::dfn[++LCA::tot] = u;
  }
}
void dfs2(int u) {
  using namespace SegT;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa[u]) {
      continue;
    }
    dfs2(v);
    if (!rot[u]) {
      rot[u] = rot[v];
    } else {
      rot[u] = merge(rot[u], rot[v], 1, n);
    }
  }
  for (auto i : Q[u]) {
    update(rot[u], 1, n, ttl[qu[i.first]], i.second);
    update(rot[u], 1, n, ttl[qv[i.first]], i.second);
  }
  if (tre[rot[u]].sum) {
    ans += tre[rot[u]].len - dep[tre[rot[u]].la];
  }
}
}  // namespace Tree
namespace LCA {
int dmin(int u, int v) {
  if (Tree::dep[u] < Tree::dep[v]) {
    return u;
  } else {
    return v;
  }
}
void init() {
  lg2[1] = 0;
  for (int i = 2; i <= tot; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  for (int i = 1; i <= tot; ++i) {
    stmin[0][i] = dfn[i];
  }
  for (int i = 1; i <= lg2[tot]; ++i) {
    for (int j = 1; j <= tot - (1 << i) + 1; ++j) {
      stmin[i][j] = dmin(stmin[i - 1][j], stmin[i - 1][j + (1 << (i - 1))]);
    }
  }
}
int lca(int u, int v) {
  u = fir[u], v = fir[v];
  if (u > v) {
    std::swap(u, v);
  }
  int k = lg2[v - u + 1];
  return dmin(stmin[k][u], stmin[k][v - (1 << k) + 1]);
}
}  // namespace LCA
namespace SegT {
#define lc(x) (tre[x].lc)
#define rc(x) (tre[x].rc)
#define sum(x) (tre[x].sum)
#define len(x) (tre[x].len)
#define la(x) (tre[x].la)
#define lp(x) (tre[x].lp)
#define rp(x) (tre[x].rp)
void pushup(int x) {
  sum(x) = sum(lc(x)) + sum(rc(x));
  if (sum(lc(x)) || sum(rc(x))) {
    if (sum(lc(x)) && sum(rc(x))) {
      lp(x) = lp(lc(x));
      rp(x) = rp(rc(x));
      la(x) = LCA::lca(la(lc(x)), la(rc(x)));
      len(x) = len(lc(x)) + len(rc(x)) - Tree::dep[LCA::lca(rp(lc(x)), lp(rc(x)))];
    } else {
      if (sum(lc(x))) {
        lp(x) = lp(lc(x));
        rp(x) = rp(lc(x));
        la(x) = la(lc(x));
        len(x) = len(lc(x));
      } else {
        lp(x) = lp(rc(x));
        rp(x) = rp(rc(x));
        la(x) = la(rc(x));
        len(x) = len(rc(x));
      }
    }
  }
}
void update(int &x, int xl, int xr, int ux, int num) {
  if (!x) {
    x = ++tot;
  }
  if (xl == xr) {
    sum(x) += num;
    lp(x) = rp(x) = la(x) = Tree::ltt[xl];
    len(x) = Tree::dep[Tree::ltt[xl]];
    return;
  }
  int xm = (xl + xr) >> 1;
  if (ux <= xm) {
    update(tre[x].lc, xl, xm, ux, num);
  } else {
    update(tre[x].rc, xm + 1, xr, ux, num);
  }
  pushup(x);
}
int merge(int x, int y, int xl, int xr) {
  if (!x || !y) {
    return x + y;
  }
  if (xl == xr) {
    sum(x) += sum(y);
    lp(x) = rp(x) = la(x) = Tree::ltt[xl];
    len(x) = Tree::dep[Tree::ltt[xl]];
    return x;
  }
  int xm = (xl + xr) >> 1;
  lc(x) = merge(lc(x), lc(y), xl, xm);
  rc(x) = merge(rc(x), rc(y), xm + 1, xr);
  pushup(x);
  return x;
}
#undef lc
#undef rc
#undef sum
#undef len
#undef lca
#undef lp
#undef rp
}  // namespace SegT

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
