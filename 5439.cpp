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

template <class T> void read(T &);
template <class T> void write(const T &);

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

const int N = 300005;
const int Mod = 998244353;

void add(int u, int v);
void add1(int u, int v);
void dfs0(int u);
void dfs1(int u);
void dfs2(int u);
void predfs(int u);
void calcdfs(int u);
void fixdfs(int u);

class Node {
public:
  int sum, tag;
} tre[N << 2];
int hed[N], nxt[N], to[N], id;
int hed1[N], nxt1[N], to1[N], siz1[N], id1;
int dep[N], siz[N], fa[N], son[N], top[N], ttl[N], id2;
int sum1[N], sum2[N];
int map[N];
int ans;
int n, m;

int main() {
  read(n), read(m);
  int rot1 = 0;
  for (int i = 1; i <= n; ++i) {
    int fa;
    read(fa);
    if (!fa) {
      rot1 = i;
    } else {
      add1(fa, i);
    }
  }
  dfs0(rot1);
  scanf("%*d");
  for (int i = 2; i <= m; ++i) {
    int fa;
    read(fa);
    add(fa, i);
  }
  scanf("%*s");
  dfs1(1);
  top[1] = 1;
  dfs2(1);
  for (int i = 1; i <= n; ++i) {
    read(map[i]);
    sum1[map[i]] = (sum1[map[i]] + siz1[i]) % Mod;
  }
  predfs(1);
  sum1[1] = 0;
  calcdfs(1);
  for (int i = 1; i <= n; ++i) {
    ans = (ans + sum2[map[i]] * 1ll * siz1[i] % Mod) % Mod;
    ans = (ans - siz1[i] * 1ll * siz1[i] % Mod * dep[map[i]] % Mod + Mod) % Mod;
  }
  ans = ans * 1ll * (Mod + 1) / 2 % Mod;
  fixdfs(rot1);
  write(ans), EL;
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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
void add1(int u, int v) {
  nxt1[++id1] = hed1[u];
  hed1[u] = id1;
  to1[id1] = v;
}
void dfs0(int u) {
  siz1[u] = 1;
  for (int i = hed1[u]; i; i = nxt1[i]) {
    int v = to1[i];
    dfs0(v);
    siz1[u] += siz1[v];
  }
}
void dfs1(int u) {
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    dep[v] = dep[u] + 1;
    fa[v] = u;
    dfs1(v);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
}
void dfs2(int u) {
  ttl[u] = ++id2;
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
void predfs(int u) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    predfs(v);
    sum1[u] = (sum1[u] + sum1[v]) % Mod;
  }
}
void calcdfs(int u) {
  sum2[u] = (sum2[fa[u]] + sum1[u]) % Mod;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    calcdfs(v);
  }
}
void pushdown(int x, int xl, int xr) {
  if (tre[x].tag) {
    int xm = (xl + xr) >> 1;
    tre[x << 1].sum =
        (tre[x << 1].sum + tre[x].tag * 1ll * (xm - xl + 1) % Mod) % Mod;
    tre[x << 1 | 1].sum =
        (tre[x << 1 | 1].sum + tre[x].tag * 1ll * (xr - xm) % Mod) % Mod;
    tre[x << 1].tag = (tre[x << 1].tag + tre[x].tag) % Mod;
    tre[x << 1 | 1].tag = (tre[x << 1 | 1].tag + tre[x].tag) % Mod;
    tre[x].tag = 0;
  }
}
void pushup(int x) {
  tre[x].sum = (tre[x << 1].sum + tre[x << 1 | 1].sum) % Mod;
}
void update(int x, int xl, int xr, int ul, int ur, int num) {
  if (ul <= xl && xr <= ur) {
    tre[x].sum = (tre[x].sum + num * 1ll * (xr - xl + 1) % Mod) % Mod;
    tre[x].tag = (tre[x].tag + num) % Mod;
    return;
  }
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    update(x << 1, xl, xm, ul, ur, num);
  }
  if (ur > xm) {
    update(x << 1 | 1, xm + 1, xr, ul, ur, num);
  }
  pushup(x);
}
int query(int x, int xl, int xr, int ql, int qr) {
  if (ql <= xl && xr <= qr) {
    return tre[x].sum;
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
void update(int x, int num) {
  while (x) {
    update(1, 1, m, ttl[top[x]], ttl[x], num);
    x = fa[top[x]];
  }
  update(1, 1, m, ttl[1], ttl[1], (Mod - num) % Mod);
}
int query(int x) {
  int ans = 0;
  while (x) {
    ans = (ans + query(1, 1, m, ttl[top[x]], ttl[x])) % Mod;
    x = fa[top[x]];
  }
  return ans;
}
void fixdfs(int u) {
  ans = (ans + query(map[u]) * 1ll * siz1[u] % Mod) % Mod;
  for (int i = hed1[u]; i; i = nxt1[i]) {
    int v = to1[i];
    update(map[u], (n - siz1[u] - siz1[v] + Mod) % Mod);
    fixdfs(v);
    update(map[u], (siz1[u] + siz1[v] - n + Mod) % Mod);
  }
}
