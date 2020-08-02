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

const int N = 40001;
const int M = 80001;

void add(int u, int v);
void dfs1(int u);
void dfs2(int u);
void dfs3(int u);
int lca(int u, int v);

int hed[N], nxt[M], to[M], id;
int fa[N], dep[N], siz[N], son[N], top[N];
int mxd[N];
int kid[N], num;
std::bitset<N> S[81][81], tmp;
int fk[N];
int sta[N], stp;
int all[N], tot;
int a[N];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(all[i]);
    a[i] = all[i];
  }
  sort(all + 1, all + n + 1);
  tot = std::unique(all + 1, all + n + 1) - all - 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = std::lower_bound(all + 1, all + tot + 1, a[i]) - all - 1;
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v);
    add(v, u);
  }
  dep[1] = 1;
  dfs1(1);
  if (!kid[1]) {
    kid[1] = ++num;
  }
  sta[stp = 1] = 1;
  dfs2(1);
  top[1] = 1;
  dfs3(1);
  int lasans = 0;
  while (m--) {
    int u, v;
    read(u), read(v);
    u ^= lasans;
    tmp.reset();
    int l = lca(u, v);
    while (u != l && !kid[u]) {
      tmp.set(a[u]);
      u = fa[u];
    }
    while (v != l && !kid[v]) {
      tmp.set(a[v]);
      v = fa[v];
    }
    if (u != l) {
      int pre = u;
      while (dep[fk[u]] >= dep[l]) {
        u = fk[u];
      }
      if (u != pre) {
        tmp |= S[kid[u]][kid[pre]];
      }
      while (u != l) {
        tmp.set(a[u]);
        u = fa[u];
      }
    }
    if (v != l) {
      int pre = v;
      while (dep[fk[v]] >= dep[l]) {
        v = fk[v];
      }
      if (v != pre) {
        tmp |= S[kid[v]][kid[pre]];
      }
      while (v != l) {
        tmp.set(a[v]);
        v = fa[v];
      }
    }
    tmp.set(a[l]);
    write(lasans = tmp.count()), EL;
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
  mxd[u] = dep[u];
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa[u]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      dfs1(v);
      siz[u] += siz[v];
      if (mxd[v] > mxd[u]) {
        mxd[u] = mxd[v];
      }
      if (siz[v] > siz[son[u]]) {
        son[u] = v;
      }
    }
  }
  if (mxd[u] - dep[u] >= 500) {
    kid[u] = ++num;
    mxd[u] = dep[u];
  }
}
void dfs2(int u) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa[u]) {
      if (kid[v]) {
        int it = kid[sta[stp]], iv = kid[v];
        for (int j = v; j != sta[stp]; j = fa[j]) {
          S[it][iv].set(a[j]);
        }
        for (int j = 1; j < stp; ++j) {
          (S[kid[sta[j]]][iv] |= S[kid[sta[j]]][it]) |= S[it][iv];
        }
        fk[v] = sta[stp];
        sta[++stp] = v;
      }
      dfs2(v);
      if (kid[v]) {
        --stp;
      }
    }
  }
}
void dfs3(int u) {
  if (son[u]) {
    top[son[u]] = top[u];
    dfs3(son[u]);
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != son[u] && v != fa[u]) {
      dfs3(top[v] = v);
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
