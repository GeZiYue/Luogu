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
const int N = 105;
const int M = 5205;

void add(int, int, int);
bool dinic_bfs();
int dinic_dfs(int, int);
int dinic();

int hed[N], cur[N], nxt[M], to[M], flw[M], id = 1;
int dep[N];
int que[N], qh, qt;
int Pt, S, T;
int ans;
int edg[55];
int n, m;

int main () {
  std::string str;
  std::getline(std::cin, str);
  std::stringstream s;
  s << str;
  s >> n >> m;
  Pt = T = n + m + 2, S = n + m + 1;
  for (int i = 1; i <= n; ++i) {
    std::string str;
    std::getline(std::cin, str);
    std::stringstream s;
    s << str;
    int a;
    s >> a;
    ans += a;
    add(S, i, a);
    edg[i] = id;
    add(i, S, 0);
    int v;
    while (s >> v) {
      add(i, v + n, iinf);
      add(v + n, i, 0);
    }
  }
  for (int i = 1; i <= m; ++i) {
    int a;
    read(a);
    add(i + n, T, a);
    add(T, i + n, 0);
  }
  ans -= dinic();
  dinic_bfs();
  for (int i = 1; i <= n; ++i) {
    if (~dep[i]) {
      write(i), SP;
    }
  }
  EL;
  for (int i = 1; i <= m; ++i) {
    if (~dep[i + n]) {
      write(i), SP;
    }
  }
  EL;
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

void add(int u, int v, int f) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  flw[id] = f;
}
bool dinic_bfs() {
  for (int i = 1; i <= Pt; ++i) {
    dep[i] = -1;
    cur[i] = hed[i];
  }
  que[qh = qt = 1] = S;
  dep[S] = 0;
  while (qh <= qt) {
    int u = que[qh++];
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if ((!~dep[v]) && flw[i]) {
        dep[v] = dep[u] + 1;
        que[++qt] = v;
      }
    }
  }
  return ~dep[T];
}
int dinic_dfs(int u, int f) {
  if (u == T || !f) {
    return f;
  }
  int ans = 0;
  for (int i = cur[u]; i; i = nxt[i]) {
    cur[u] = i;
    int v = to[i];
    if (dep[v] == dep[u] + 1) {
      int now = dinic_dfs(v, min(f, flw[i]));
      flw[i] -= now;
      flw[i ^ 1] += now;
      f -= now;
      ans += now;
      if (!f) {
        break;
      }
    }
  }
  return ans;
}
int dinic() {
  int ans = 0;
  while (dinic_bfs()) {
    ans += dinic_dfs(S, iinf);
  }
  return ans;
}
