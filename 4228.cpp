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
using std::sort;

void add(int, int);
int cmp(int, int);
void dfs1(int, int);
void dfs2(int, int, int);

const int N = 100005;
const int M = 200005;

int hed[N], nxt[M], to[M], id;
int dep[N], siz[N], fson[N], sson[N], f[N];
bool ans[N];
int n;

int main () {
  int w, t;
  read(w), read(t);
  while (t--) {
    memset(hed, 0, sizeof(hed));
    memset(fson, 0, sizeof(fson));
    memset(sson, 0, sizeof(sson));
    memset(ans, 0, sizeof(ans));
    id = 0;
    read(n);
    for (int i = 1; i < n; ++i) {
      int u, v;
      read(u), read(v);
      add(u, v), add(v, u);
    }
    dep[1] = 1;
    dfs1(1, 0);
    dfs2(1, 0, 0);
    if (w == 3) {
      putchar(ans[1] + '0');
    } else {
      for (int i = 1; i <= n; ++i) {
        putchar(ans[i] + '0');
      }
    }
    EL;
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
int cmp(int i, int j) {
  return siz[i] > siz[j] ? i : j;
}
void dfs1(int u, int fa) {
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa) {
      dep[v] = dep[u] + 1;
      dfs1(v, u);
      siz[u] += siz[v];
      if (siz[v] > siz[fson[u]]) {
        sson[u] = fson[u];
        fson[u] = v;
      } else {
        if (siz[v] > siz[sson[u]]) {
          sson[u] = v;
        }
      }
    }
  }
  if (siz[fson[u]] - (f[fson[u]] << 1) <= siz[u] - 1 - siz[fson[u]]) {
    f[u] = (siz[u] - 1) / 2;
  } else {
    f[u] = f[fson[u]] + siz[u] - 1 - siz[fson[u]];
  }
}
void dfs2(int u, int fa, int s) {
  int tmp = cmp(s, fson[u]);
  if (siz[tmp] - (f[tmp] << 1) <= n - dep[u] - siz[tmp]) {
    ans[u] = (n & 1) == (dep[u] & 1);
  }
  if (fson[u]) {
    dfs2(fson[u], u, cmp(s, sson[u]));
  }
  tmp = cmp(s, fson[u]);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa && v != fson[u]) {
      dfs2(v, u, tmp);
    }
  }
}
