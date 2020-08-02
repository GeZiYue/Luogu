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

const int N = 50005;
const int M = 100005;
const int Mod = 998244353;

void add(int u, int v);
void dfs1(int u);
void dfs2(int u);
int pow(int a, int b, int m);
void build(int x, int xl, int xr);
void update(int x);
int query(int x);

int hed[N], nxt[M], to[M], id;
int fa[N], dep[N], siz[N], son[N], top[N], dfn[N], bck[N], id2;
int power[N];
int sum[N << 2], val[N << 2], tag[N << 2];
std::vector<int> v[N];
int qry[N], ans[N];
int n, q, k;

int main () {
  read(n), read(q), read(k);
  for (int i = 1; i <= n; ++i) {
    power[i] = pow(i, k, Mod);
  }
  for (int i = 2; i <= n; ++i) {
    int fa;
    read(fa);
    add(fa, i);
  }
  dep[1] = 1;
  dfs1(1);
  top[1] = 1;
  dfs2(1);
  build(1, 1, n);
  for (int i = 1; i <= q; ++i) {
    int x, y;
    read(x), read(y);
    v[x].push_back(i);
    qry[i] = y;
  }
  for (int i = 1; i <= n; ++i) {
    update(i);
    for (int j = 0; j < v[i].size(); ++j) {
      ans[v[i][j]] = query(qry[v[i][j]]);
    }
  }
  for (int i = 1; i <= q; ++i) {
    write(ans[i]), EL;
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

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs1(int u) {
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    fa[v] = u;
    dep[v] = dep[u] + 1;
    dfs1(v);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
}
void dfs2(int u) {
  dfn[u] = ++id2;
  bck[id2] = u;
  if (son[u]) {
    top[son[u]] = top[u];
    dfs2(son[u]);
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != son[u]) {
      top[v] = v;
      dfs2(v);
    }
  }
}
int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
void build(int x, int xl, int xr) {
  if (xl == xr) {
    val[x] = (power[dep[bck[xl]]] - power[dep[bck[xl]] - 1] + Mod) % Mod;
    return;
  }
  int xm = (xl + xr) >> 1;
  build(x << 1, xl, xm);
  build(x << 1 | 1, xm + 1, xr);
  val[x] = (val[x << 1] + val[x << 1 | 1]) % Mod;
}
void pushdown(int x, int xl, int xr) {
  int xm = (xl + xr) >> 1;
  if (tag[x]) {
    sum[x << 1] = (sum[x << 1] + tag[x] * 1ll * val[x << 1] % Mod) % Mod;
    sum[x << 1 | 1] = (sum[x << 1 | 1] + tag[x] * 1ll * val[x << 1 | 1] % Mod) % Mod;
    tag[x << 1] += tag[x];
    tag[x << 1 | 1] += tag[x];
    tag[x] = 0;
  }
}
void update(int x, int xl, int xr, int ul, int ur) {
  if (ul <= xl && xr <= ur) {
    sum[x] = (sum[x] + val[x]) % Mod;
    ++tag[x];
    return;
  }
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    update(x << 1, xl, xm, ul, ur);
  }
  if (ur > xm) {
    update(x << 1 | 1, xm + 1, xr, ul, ur);
  }
  sum[x] = (sum[x << 1] + sum[x << 1 | 1]) % Mod;
}
int query(int x, int xl, int xr, int ql, int qr) {
  if (ql <= xl && xr <= qr) {
    return sum[x];
  }
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  int ans = 0;
  if (ql <= xm) {
    ans = (ans + query(x << 1, xl, xm, ql, qr)) % Mod;
  }
  if (qr > xm) {
    ans = (ans + query(x << 1 | 1, xm + 1, xr, ql, qr)) % Mod;
  }
  return ans;
}
void update(int x) {
  while (x) {
    update(1, 1, n, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
}
int query(int x) {
  int ans = 0;
  while (x) {
    ans = (ans + query(1, 1, n, dfn[top[x]], dfn[x])) % Mod;
    x = fa[top[x]];
  }
  return ans;
}
