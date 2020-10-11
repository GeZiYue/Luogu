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
#include <numeric>
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

const int N = 200005;
const int M = 800005;

void add(int u, int v, int w);
void add2(int u, int v);
void Dijkstra(int S);
void Kruskal();
int query(int x, int a);

int hed[N], nxt[M], to[M], dis[M], id;
int u[N << 1], v[N << 1], w[N << 1], d[N << 1];
int delta[N];
bool vis[N];
int faa[N << 1];
int hed2[N << 1], nxt2[N << 1], to2[N << 1], id2;
int fa[N << 1][23], mind[N << 1], wat[N << 1], dep[N << 1];
int lg2[N << 1];
int tot;
int n, m;

int main() {
  for (int i = 2; i < (N << 1); ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  int T;
  read(T);
  while (T--) {
    id = id2 = tot = 0;
    memset(hed, 0, sizeof(hed));
    memset(hed2, 0, sizeof(hed2));
    memset(fa, 0, sizeof(fa));
    read(n), read(m);
    for (int i = 1; i <= m; ++i) {
      read(u[i]), read(v[i]), read(w[i]), read(d[i]);
      add(u[i], v[i], w[i]);
      add(v[i], u[i], w[i]);
    }
    Dijkstra(1);
    for (int i = 1; i <= n; ++i) {
      mind[i] = delta[i];
      mind[i + n] = iinf;
    }
    Kruskal();
    int q, k, s;
    read(q), read(k), read(s);
    int lasans = 0;
    for (int i = 1; i <= q; ++i) {
      int x, a;
      read(x), read(a);
      x = (x + lasans * 1ll * k - 1) % n + 1;
      a = (a + lasans * 1ll * k) % (s + 1);
      write(lasans = query(x, a)), EL;
    }
  }
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

void add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
void add2(int u, int v) {
  nxt2[++id2] = hed2[u];
  hed2[u] = id2;
  to2[id2] = v;
}
void Dijkstra(int S) {
  for (int i = 1; i <= n; ++i) {
    delta[i] = iinf;
    vis[i] = false;
  }
  delta[S] = 0;
  std::priority_queue<pii> pq;
  pq.push(pii(0, S));
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = true;
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (vis[v]) {
        continue;
      }
      if (delta[u] + dis[i] < delta[v]) {
        delta[v] = delta[u] + dis[i];
        pq.push(pii(-delta[v], v));
      }
    }
  }
}
int find(int x) { return faa[x] == x ? x : faa[x] = find(faa[x]); }
void dfs(int u) {
  for (int i = 1; i <= lg2[dep[u]]; ++i) {
    fa[u][i] = fa[fa[u][i - 1]][i - 1];
  }
  for (int i = hed2[u]; i; i = nxt2[i]) {
    int v = to2[i];
    if (v != fa[u][0]) {
      fa[v][0] = u;
      dep[v] = dep[u] + 1;
      dfs(v);
      mind[u] = min(mind[u], mind[v]);
    }
  }
}
void Kruskal() {
  std::vector<int> V(m);
  std::iota(V.begin(), V.end(), 1);
  std::sort(V.begin(), V.end(), [&](int i, int j) { return d[i] > d[j]; });
  std::iota(faa + 1, faa + (n << 1), 1);
  int cnt = 0;
  tot = n;
  for (auto i : V) {
    int fu = find(u[i]), fv = find(v[i]);
    if (fu != fv) {
      add2(++tot, fu);
      add2(tot, fv);
      wat[tot] = d[i];
      faa[fu] = faa[fv] = tot;
      ++cnt;
      if (cnt == n - 1) {
        break;
      }
    }
  }
  dep[tot] = 0;
  fa[tot][0] = 0;
  dfs(tot);
}
int query(int x, int a) {
  for (int i = lg2[dep[x]]; i >= 0; --i) {
    if (wat[fa[x][i]] > a) {
      x = fa[x][i];
    }
  }
  return mind[x];
}
