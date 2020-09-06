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

const int N = 500005;
const int M = 1000005;

void add(int u, int v);
void dfs(int u, int fa);

ll f[N][2];
int a[N];
int hed[N], nxt[M], to[M], id;
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  dfs(1, 0);
  write(f[1][1]), EL;
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
void dfs(int u, int fa) {
  int deg = 0;
  ll S = 0;
  std::vector<ll> V;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa) {
      ++deg;
      dfs(v, u);
      S += max(a[v] + f[v][0], m + f[v][1]);
      if (a[v] < a[u]) {
        V.push_back(max(a[v] + f[v][0], a[u] + f[v][1]) - max(a[v] + f[v][0], m + f[v][1]));
      } else {
        V.push_back(a[u] + f[v][0] - max(a[v] + f[v][0], m + f[v][1]));
      }
    }
  }
  if (!deg) {
    f[u][0] = 0, f[u][1] = -iinf;
    return;
  }
  if (fa) {
    ++deg;
  }
  f[u][0] = f[u][1] = S;
  std::sort(V.begin(), V.end(), std::greater<int>());
  for (int i = 0; i < (deg / 2); ++i) {
    f[u][0] += V[i];
    f[u][1] += V[i];
  }
  f[u][1] += V[deg / 2];
  if (fa && deg == 2) {
    f[u][1] = -iinf;
  }
}
