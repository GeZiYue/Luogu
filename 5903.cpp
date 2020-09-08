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
#include <ctime>
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

const int N = 500001;

unsigned getrnd(unsigned x);
void dfs1(int u);
void dfs2(int u);
int query(int u, int k);

int lg2[N];
int mxd[N], dep[N], son[N], fa[N][20], top[N];
std::vector<int> up[N], down[N], edg[N];
int root;
int n, q;
unsigned s;

int main () {
  read(n), read(q), read(s);
  lg2[1] = 0;
  for (int i = 2; i <= n; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  for (int i = 1; i <= n; ++i) {
    int fa;
    read(fa);
    if (!fa) {
      root = i;
    } else {
      edg[fa].push_back(i);
    }
  }
  dfs1(root);
  top[root] = root;
  dfs2(root);
  int lasans = 0;
  ll ans = 0;
  for (int i = 1; i <= q; ++i) {
    int x = (getrnd(s) ^ lasans) % n + 1, k = (getrnd(s) ^ lasans) % (dep[x] + 1);
    ans ^= i * 1ll * (lasans = query(x, k));
  }
  write(ans), EL;
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

unsigned getrnd(unsigned x) {
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return s = x;
}
void dfs1(int u) {
  for (int i = 1; i <= lg2[dep[u]]; ++i) {
    fa[u][i] = fa[fa[u][i - 1]][i - 1];
  }
  mxd[u] = dep[u];
  for (auto v : edg[u]) {
    fa[v][0] = u;
    dep[v] = dep[u] + 1;
    dfs1(v);
    if (mxd[v] > mxd[u]) {
      mxd[u] = mxd[v];
      son[u] = v;
    }
  }
}
void dfs2(int u) {
  if (top[u] == u) {
    for (int i = 0, x = u; i <= mxd[u] - dep[u]; ++i) {
      up[u].push_back(x);
      x = fa[x][0];
    }
    for (int i = 0, x = u; i <= mxd[u] - dep[u]; ++i) {
      down[u].push_back(x);
      x = son[x];
    }
  }
  if (son[u]) {
    top[son[u]] = top[u];
    dfs2(son[u]);
  }
  for (auto v : edg[u]) {
    if (v != son[u]) {
      top[v] = v;
      dfs2(v);
    }
  }
}
int query(int u, int k) {
  if (!k) {
    return u;
  }
  u = fa[u][lg2[k]];
  k -= (1 << lg2[k]);
  k -= dep[u] - dep[top[u]];
  u = top[u];
  if (k < 0) {
    return down[u][-k];
  } else {
    return up[u][k];
  }
}
