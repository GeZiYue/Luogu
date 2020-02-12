#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
void read(T&);
template<class T>
void write(const T&);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;

const int N = 200005;
const int M = 400005;
const int K = 20;

void add(int, int, int);
void insert(int &, int, int, int, int);
int query(int, int, int, int, int, int);
void dfs(int);
int lca(int, int);
int length(int, int);
int query(int, int, int);

class Node {
public:
  int lc, rc;
  int val;
};

int hed[N], nxt[M], to[M], val[M], id;
int dep[N], fa[N][K], sum[N], siz[N], dfn[N], tot;
int rot[N];
Node tre[N * K];
int cnt;
int lg2[N];
int LCA[N][K];
int n, q;

int main () {
  read(n), read(q);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    add(u, v, w), add(v, u, w);
  }
  lg2[1] = 0;
  for (int i = 2; i <= n; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  dfs(1);
  for (int i = 1; i <= lg2[n]; ++i) {
    for (int j = 1; j <= n; ++j) {
      fa[j][i] = fa[fa[j][i - 1]][i - 1];
    }
  }
  for (int i = 1; i <= n; ++i) {
    LCA[i][0] = i;
  }
  for (int i = 1; i <= lg2[n]; ++i) {
    for (int j = 1; j <= n - (1 << i) + 1; ++j) {
      LCA[j][i] = lca(LCA[j][i - 1], LCA[j + (1 << (i - 1))][i - 1]);
    }
  }
  int lasans = 0;
  for (int i = 1; i <= q; ++i) {
    int p, l, r;
    read(p), read(l), read(r);
    p ^= lasans, l ^= lasans, r ^= lasans;
    int k = lg2[r - l + 1];
    int Lca = lca(LCA[l][k], LCA[r - (1 << k) + 1][k]);
    int x = query(l, r, p);
    if (dep[x] > dep[Lca]) {
      write(lasans = length(x, p)), EL;
    } else {
      write(lasans = length(Lca, p)), EL;
    }
  }
  return 0;
}

template<class T>
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
template<class T>
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

void add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  val[id] = w;
  to[id] = v;
}
void insert(int &x, int xl, int xr, int pos, int num) {
  tre[++tot] = tre[x];
  x = tot;
  tre[x].val += num;
  if (xl == xr) {
    return;
  }
  int xm = (xl + xr) >> 1;
  if (xm >= pos) {
    insert(tre[x].lc, xl, xm, pos, num);
  } else {
    insert(tre[x].rc, xm + 1, xr, pos, num);
  }
}
int query(int lx, int rx, int xl, int xr, int ql, int qr) {
  if (ql <= xl && xr <= qr) {
    return tre[rx].val - tre[lx].val;
  }
  int xm = (xl + xr) >> 1;
  int ans = 0;
  if (xm >= ql) {
    ans += query(tre[lx].lc, tre[rx].lc, xl, xm, ql, qr);
  }
  if (xm < qr) {
    ans += query(tre[lx].rc, tre[rx].rc, xm + 1, xr, ql, qr);
  }
  return ans;
}
void dfs(int u) {
  dfn[u] = ++cnt;
  insert(rot[cnt] = rot[cnt - 1], 1, n, u, 1);
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa[u][0]) {
      dep[v] = dep[u] + 1;
      fa[v][0] = u;
      sum[v] = sum[u] + val[i];
      dfs(v);
      siz[u] += siz[v];
    }
  }
}
int lca(int a, int b) {
  if (dep[a] < dep[b]) {
    a ^= b ^= a ^= b;
  }
  int k = dep[a] - dep[b];
  {
    int now = 0;
    while (k) {
      if (k & 1) {
        a = fa[a][now];
      }
      ++now;
      k >>= 1;
    }
  }
  if (a == b) {
    return a;
  }
  for (int i = lg2[n]; i >= 0; --i) {
    if (fa[a][i] ^ fa[b][i]) {
      a = fa[a][i];
      b = fa[b][i];
    }
  }
  return fa[a][0];
}
int length(int a, int b) {
  return sum[a] + sum[b] - (sum[lca(a, b)] << 1);
}
int query(int l, int r, int x) {
  if (query(rot[dfn[x] - 1], rot[dfn[x] + siz[x] - 1], 1, n, l, r)) {
    return x;
  }
  for (int i = lg2[n]; i >= 0; --i) {
    int tmp = fa[x][i];
    if (tmp && !query(rot[dfn[tmp] - 1], rot[dfn[tmp] + siz[tmp] - 1], 1, n, l, r)) {
      x = tmp;
    }
  }
  return fa[x][0];
}
