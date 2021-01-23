#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef long long ll;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

constexpr int N = 10005;
constexpr int M = 200005;

void add(int, int, int);
ll Dinic();

int hed[N], cur[N], nxt[M], to[M], flw[M], id = 1;
int que[N], qh, qt;
int dep[N];
int n, m, S, T;

int main() {
  read(n), read(m), read(S), read(T);
  for (int i = 1; i <= m; ++i) {
    int u, v, f;
    read(u), read(v), read(f);
    add(u, v, f);
    add(v, u, 0);
  }
  write(Dinic()), EL;
  return 0;
}

template <class T>
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
template <class T>
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
bool Dinic_bfs() {
  for (int i = 1; i <= n; ++i) {
    dep[i] = -1;
    cur[i] = hed[i];
  }
  dep[que[qh = qt = 1] = S] = 0;
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
ll Dinic_dfs(int u, int f) {
  if (u == T || f == 0) {
    return f;
  }
  int ans = 0;
  for (int i = cur[u]; i; i = nxt[i]) {
    cur[u] = i;
    int v = to[i];
    if (dep[v] == dep[u] + 1) {
      int now = Dinic_dfs(v, min(f, flw[i]));
      flw[i] -= now;
      flw[i ^ 1] += now;
      ans += now;
      f -= now;
      if (!f) {
        break;
      }
    }
  }
  return ans;
}
ll Dinic() {
  ll ans = 0;
  while (Dinic_bfs()) {
    ans += Dinic_dfs(S, iinf);
  }
  return ans;
}
