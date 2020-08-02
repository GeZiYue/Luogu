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
const int Mod = 201314;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

void add(int, int);
void dfs1(int);
void dfs2(int);
void update(int);
int query(int);

int hed[N], nxt[M], to[M], id;
int siz[N], fa[N], son[N], top[N], dfn[N], id2;
std::vector<int> ql[N], qr[N];
int BIT1[N], BIT2[N];
int qry[N];
int ans[N];
int n, q;

int main () {
  read(n), read(q);
  for (int i = 2; i <= n; ++i) {
    int fa;
    read(fa);
    ++fa;
    add(fa, i);
  }
  for (int i = 1; i <= q; ++i) {
    int l, r;
    read(l), read(r), read(qry[i]);
    ql[l].push_back(i);
    qr[r + 1].push_back(i);
    ++qry[i];
  }
  dfs1(1);
  top[1] = 1;
  dfs2(1);
  for (int i = 1; i <= n; ++i) {
    update(i);
    for (int j = 0; j < ql[i].size(); ++j) {
      ans[ql[i][j]] = (ans[ql[i][j]] - query(qry[ql[i][j]]) + Mod) % Mod;
    }
    for (int j = 0; j < qr[i].size(); ++j) {
      ans[qr[i][j]] = (ans[qr[i][j]] + query(qry[qr[i][j]])) % Mod;
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
    dfs1(v);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
}
void dfs2(int u) {
  dfn[u] = ++id2;
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
void update(int l, int r) {
  int i = l;
  while (i <= n) {
    BIT1[i] = (BIT1[i] + 1) % Mod;
    BIT2[i] = (BIT2[i] + l) % Mod;
    i += i & -i;
  }
  i = r + 1;
  while (i <= n) {
    BIT1[i] = (BIT1[i] + Mod - 1) % Mod;
    BIT2[i] = (BIT2[i] + Mod - (r + 1)) % Mod;
    i += i & -i;
  }
}
int queryBIT(int x) {
  int s1 = 0, s2 = 0;
  int i = x;
  while (i) {
    s1 = (s1 + BIT1[i]) % Mod;
    s2 = (s2 + BIT2[i]) % Mod;
    i -= i & -i;
  }
  return (s1 * 1ll * (x + 1) % Mod - s2 + Mod) % Mod;
}
int query(int l, int r) {
  return (queryBIT(r) - queryBIT(l - 1) + Mod) % Mod;
}
void update(int x) {
  while (x) {
    update(dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
}
int query(int x) {
  int ans = 0;
  while (x) {
    ans = (ans + query(dfn[top[x]], dfn[x])) % Mod;
    x = fa[top[x]];
  }
  return ans;
}

