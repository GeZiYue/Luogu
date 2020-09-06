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

const int N = 500005;
const int M = 1000005;
const long double eps = 1e-9;

void add(int u, int v, long double w);
void dfs1(int u, int fa);
void dfs2(int u, int fa);

long double f[N], g[N];
int hed[N], nxt[M], to[M], id;
long double e[M];
long double p[N];
int n;

int main () {
  read(n);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    add(u, v, w / 100.0);
    add(v, u, w / 100.0);
  }
  for (int i = 1; i <= n; ++i) {
    int pi;
    read(pi);
    p[i] = pi / 100.0;
  }
  dfs1(1, 0);
  g[1] = f[1];
  dfs2(1, 0);
  long double ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += 1 - g[i];
  }
  std::cout.precision(6);
  std::cout << std::fixed << ans << std::endl;
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

void add(int u, int v, long double w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  e[id] = w;
}
void dfs1(int u, int fa) {
  f[u] = 1 - p[u];
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    dfs1(v, u);
    f[u] *= (1 - e[i] + e[i] * f[v]);
  }
}
void dfs2(int u, int fa) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    if (1 - e[i] + e[i] * f[v] < eps) {
      g[v] = f[v];
    } else {
      g[v] = f[v] * (1 - e[i] + e[i] * g[u] / (1 - e[i] + e[i] * f[v]));
    }
    dfs2(v, u);
  }
}
