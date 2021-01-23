#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 200005;
constexpr int M = 400005;

namespace Graph {
int hed[N], nxt[M], to[M], id = 0;
int rhed[N], rnxt[M], rto[M], rid = 0;
ll dis[M], rdis[M];
int las[N], L[N], R[N];
bool on[N];
int V;
void add(int u, int v, int w);
void radd(int u, int v, int w);
void Dijkstra(ll *del, int S, int op);
void rDijkstra(ll *del, int S, int op);
void init();
}  // namespace Graph
namespace Seg_Tree {
int siz;
ll mini[N << 2];
void build(int x, int xl, int xr);
void update(int x, int xl, int xr, int ul, int ur, ll num);
ll query(int x, int xl, int xr, int qx);
}  // namespace Seg_Tree

ll delS[N], delT[N];
bool ons[N];
int u[N], v[N], w[N];
int lk[N];
int n, m, q;

int main() {
  using namespace Seg_Tree;
  using namespace Graph;
  read(n), read(m), read(q);
  for (int i = 1; i <= m; ++i) {
    read(u[i]), read(v[i]), read(w[i]);
    add(u[i], v[i], w[i]);
    radd(v[i], u[i], w[i]);
  }
  V = n;
  for (int i = 1; i <= q; ++i) {
    read(lk[i]);
  }
  init();
  Dijkstra(delS, 1, 1);
  rDijkstra(delT, n, 2);
  build(1, 1, siz);
  for (int u = 1; u <= n; ++u) {
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (ons[i] || delS[u] > 1e15 || delT[v] > 1e15) {
        continue;
      }
      update(1, 1, siz, L[u] + 1, R[v], delS[u] + delT[v] + dis[i]);
    }
  }
  for (int u = 1; u <= n; ++u) {
    update(1, 1, siz, L[u] + 1, R[u], delS[u] + delT[u]);
  }
  for (int i = 1; i <= q; ++i) {
    ll ans = query(1, 1, siz, i + 1);
    if (ans > 1e12) {
      puts("-1");
    } else {
      write(ans), EL;
    }
  }
  return 0;
}

namespace Graph {
void add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
void radd(int u, int v, int w) {
  rnxt[++rid] = rhed[u];
  rhed[u] = rid;
  rto[rid] = v;
  rdis[rid] = w;
}
void Dijkstra(ll *del, int S, int op) {
  for (int i = 1; i <= V; ++i) {
    del[i] = llinf;
  }
  del[S] = 0;
  std::priority_queue<std::pair<ll, int> > pq;
  pq.emplace(0, S);
  while (!pq.empty()) {
    auto [w, u] = pq.top();
    pq.pop();
    w = -w;
    if (del[u] != w) {
      continue;
    }
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (del[u] + dis[i] < del[v]) {
        del[v] = del[u] + dis[i];
        las[v] = i;
        if (op == 1 && !on[v]) {
          L[v] = L[u];
        }
        pq.emplace(-del[v], v);
      }
    }
  }
}

void rDijkstra(ll *del, int S, int op) {
  for (int i = 1; i <= V; ++i) {
    del[i] = llinf;
  }
  del[S] = 0;
  std::priority_queue<std::pair<ll, int> > pq;
  pq.emplace(0, S);
  while (!pq.empty()) {
    auto [w, u] = pq.top();
    pq.pop();
    w = -w;
    if (del[u] != w) {
      continue;
    }
    for (int i = rhed[u]; i; i = rnxt[i]) {
      int v = rto[i];
      if (del[u] + rdis[i] < del[v]) {
        del[v] = del[u] + rdis[i];
        las[v] = i;
        if (op == 2 && !on[v]) {
          R[v] = R[u];
        }
        pq.emplace(-del[v], v);
      }
    }
  }
}
void init() {
  Seg_Tree::siz = q + 1;
  for (int i = 1; i <= q; ++i) {
    L[u[lk[i]]] = R[u[lk[i]]] = i;
    on[u[lk[i]]] = true;
    ons[lk[i]] = true;
  }
  L[v[lk[q]]] = R[v[lk[q]]] = q + 1;
  on[v[lk[q]]] = true;
}
}  // namespace Graph
namespace Seg_Tree {
void build(int x, int xl, int xr) {
  mini[x] = llinf;
  if (xl == xr) {
    return;
  }
  int xm = (xl + xr) >> 1;
  build(x << 1, xl, xm), build(x << 1 | 1, xm + 1, xr);
}
void pushdown(int x) {
  mini[x << 1] = std::min(mini[x << 1], mini[x]);
  mini[x << 1 | 1] = std::min(mini[x << 1 | 1], mini[x]);
}
void update(int x, int xl, int xr, int ul, int ur, ll num) {
  if (ul > ur) {
    return;
  }
  if (ul <= xl && xr <= ur) {
    mini[x] = std::min(mini[x], num);
    return;
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    update(x << 1, xl, xm, ul, ur, num);
  }
  if (ur > xm) {
    update(x << 1 | 1, xm + 1, xr, ul, ur, num);
  }
}
ll query(int x, int xl, int xr, int qx) {
  if (xl == xr) {
    return mini[x];
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  if (qx <= xm) {
    return query(x << 1, xl, xm, qx);
  } else {
    return query(x << 1 | 1, xm + 1, xr, qx);
  }
}
}  // namespace Seg_Tree

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
