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

const int N = 1000005;
const int M = 2000005;

void add(int, int);
void dfs1(int);
void dfs2(int);
int chgrot(int);
void update(int, int);
int qlca(int, int);
int query(int, int);
int query(int);

int hed[N], nxt[M], to[M], id;
int fa[N], dep[N], siz[N], son[N], top[N], dfn[N], tot;
int val[N], vsm[N];
int BIT1[N], BIT2[N];
int sdp[N];
int rot;
int n, m, q;

int main () {
  read(n), read(m), read(q);
  m += q;
  for (int i = 1; i <= n; ++i) {
    read(val[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  dep[1] = 1;
  dfs1(1);
  top[1] = 1;
  dfs2(1);
  for (int i = 1; i <= m; ++i) {
    int type, x;
    read(type), read(x);
    if (type == 1) {
      write(chgrot(x)), EL;
    } else {
      if (type == 2) {
        int y;
        read(y);
        update(x, y);
      } else {
        if (type == 3) {
          int y;
          read(y);
          write(qlca(x, y)), EL;
        } else {
          if (type == 4) {
            int y;
            read(y);
            write(query(x, y)), EL;
          } else {
            write(query(x)), EL;
          }
        }
      }
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

void update_BIT1(int x, int num) {
  while (x <= n) {
    BIT1[x] ^= num;
    x += x & -x;
  }
}
int query_BIT1(int x) {
  int ans = 0;
  while (x) {
    ans ^= BIT1[x];
    x -= x & -x;
  }
  return ans;
}
void update_BIT2(int x, int num) {
  while (x <= n) {
    BIT2[x] ^= num;
    x += x & -x;
  }
}
int query_BIT2(int x) {
  int ans = 0;
  while (x) {
    ans ^= BIT2[x];
    x -= x & -x;
  }
  return ans;
}
void update1(int l, int r, int num) {
  update_BIT1(l, num), update_BIT1(r + 1, num);
}
int query1(int x) {
  return query_BIT1(x);
}
void update2(int x, int num) {
  update_BIT2(x, num);
}
int query2(int l, int r) {
  return query_BIT2(r) ^ query_BIT2(l - 1);
}
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs1(int u) {
  siz[u] = 1;
  sdp[dep[u] & 1] ^= val[u];
  vsm[u] = vsm[fa[u]] ^ val[u];
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa[u]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      dfs1(v);
      siz[u] += siz[v];
      if (siz[v] > siz[son[u]]) {
        son[u] = v;
      }
    }
  }
}
void dfs2(int u) {
  dfn[u] = ++tot;
  update1(dfn[u], dfn[u], vsm[u]);
  update2(dfn[u], val[u]);
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
int chgrot(int x) {
  rot = x;
  return sdp[dep[x] & 1];
}
void update(int x, int num) {
  int del = num ^ val[x];
  val[x] = num;
  sdp[dep[x] & 1] ^= del;
  update1(dfn[x], dfn[x] + siz[x] - 1, del);
  update2(dfn[x], del);
}
int lca(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) {
      u ^= v ^= u ^= v;
    }
    u = fa[top[u]];
  }
  return dep[u] < dep[v] ? u : v;
}
int qlca(int u, int v) {
  int ans = lca(u, v);
  int tmp = lca(u, rot);
  if (dep[tmp] > dep[ans]) {
    ans = tmp;
  }
  tmp = lca(v, rot);
  if (dep[tmp] > dep[ans]) {
    ans = tmp;
  }
  return ans;
}
int qson(int u, int v) {
  while (true) {
    if (fa[top[v]] == u) {
      return top[v];
    } else {
      if (dep[top[v]] <= dep[u]) {
        return son[u];
      } else {
        v = fa[top[v]];
      }
    }
  }
}
int query(int u, int v) {
  return query1(dfn[u]) ^ query1(dfn[v]) ^ val[lca(u, v)];
}
int query(int u) {
  if (dfn[u] < dfn[rot] && dfn[rot] < dfn[u] + siz[u]) {
    int s = qson(u, rot);
    return sdp[0] ^ sdp[1] ^ query2(dfn[s], dfn[s] + siz[s] - 1);
  } else {
    return query2(dfn[u], dfn[u] + siz[u] - 1);
  }
}
