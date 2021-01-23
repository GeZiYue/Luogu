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

constexpr int N = 505;
constexpr int M = 3005;

namespace Flow {
int hed[N], nxt[M], to[M], flw[M], id = 1;
int dep[N], cur[N];
int S, T;
void add(int u, int v, int w);
bool dinic_bfs();
int dinic_dfs(int u, int res);
int dinic();
}  // namespace Flow
namespace GH_Tree {
int hed[N], nxt[N << 1], to[N << 1], dis[N << 1], id;
void add(int u, int v, int w);
void build(std::vector<int> V);
int anc[N][10], mini[N][10], dep[N];
void dfs(int u);
int query(int u, int v);
}  // namespace GH_Tree

int lg2[N];
int n, m, q;

int main() {
  read(n), read(m);
  lg2[1] = 0;
  for (int i = 2; i <= n; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  std::vector<int> now;
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    Flow::add(u, v, w), Flow::add(v, u, w);
  }
  for (int i = 1; i <= n; ++i) {
    now.push_back(i);
  }
  GH_Tree::build(now);
  GH_Tree::dfs(1);
  read(q);
  while (q--) {
    int u, v;
    read(u), read(v);
    write(GH_Tree::query(u, v)), EL;
  }
  return 0;
}

namespace Flow {
void add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  flw[id] = w;
}
bool dinic_bfs() {
  for (int i = 1; i <= n; ++i) {
    dep[i] = -1;
    cur[i] = hed[i];
  }
  dep[S] = 0;
  std::queue<int> q;
  q.push(S);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (dep[v] == -1 && flw[i]) {
        dep[v] = dep[u] + 1;
        q.push(v);
      }
    }
  }
  return dep[T] != -1;
}
int dinic_dfs(int u, int rem) {
  if (u == T || !rem) {
    return rem;
  }
  int ans = 0;
  for (int i = cur[u]; i; i = nxt[i]) {
    cur[u] = i;
    int v = to[i];
    if (dep[v] == dep[u] + 1) {
      int now = dinic_dfs(v, std::min(rem, flw[i]));
      ans += now;
      rem -= now;
      flw[i] -= now;
      flw[i ^ 1] += now;
      if (!rem) {
        break;
      }
    }
  }
  return ans;
}
int dinic() {
  for (int i = 2; i <= id; i += 2) {
    flw[i] = flw[i + 1] = (flw[i] + flw[i ^ 1]) / 2;
  }
  int ans = 0;
  while (dinic_bfs()) {
    ans += dinic_dfs(S, iinf);
  }
  return ans;
}
}  // namespace Flow
namespace GH_Tree {
void add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
void build(std::vector<int> V) {
  if (V.size() <= 1) {
    return;
  }
  int u = V[0], v = V[1];
  Flow::S = u, Flow::T = v;
  int now = Flow::dinic();
  add(u, v, now);
  add(v, u, now);
  std::vector<int> Vs, Vt;
  for (auto u : V) {
    if (Flow::dep[u] != -1) {
      Vs.push_back(u);
    } else {
      Vt.push_back(u);
    }
  }
  build(Vs), build(Vt);
}
void dfs(int u) {
  for (int i = 1; i <= lg2[dep[u]]; ++i) {
    anc[u][i] = anc[anc[u][i - 1]][i - 1];
    mini[u][i] = std::min(mini[u][i - 1], mini[anc[u][i - 1]][i - 1]);
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == anc[u][0]) {
      continue;
    }
    anc[v][0] = u;
    dep[v] = dep[u] + 1;
    mini[v][0] = dis[i];
    dfs(v);
  }
}
int query(int u, int v) {
  int now = iinf;
  if (dep[u] < dep[v]) {
    std::swap(u, v);
  }
  int d = dep[u] - dep[v];
  for (int i = 0; i < 10; ++i) {
    if (d >> i & 1) {
      now = std::min(now, mini[u][i]);
      u = anc[u][i];
    }
  }
  if (u == v) {
    return now;
  }
  for (int i = 9; i >= 0; --i) {
    if (anc[u][i] != anc[v][i]) {
      now = std::min(now, mini[u][i]);
      now = std::min(now, mini[v][i]);
      u = anc[u][i];
      v = anc[v][i];
    }
  }
  now = std::min(now, mini[u][0]);
  now = std::min(now, mini[v][0]);
  return now;
}
}  // namespace GH_Tree

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
