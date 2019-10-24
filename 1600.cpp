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
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 300005;
const int M = 600005;

void add(int, int);
void qadd(int, int, int);
void tarjan(int);
void dfs1(int, int);
void dfs2(int, int);

int hed[N], nxt[M], to[M], id;
int qhed[N], qnxt[M], qto[M], qnum[M], qid;
int w[N];
int dep[N];
int u[N], v[N];
int fa[N];
int lca[N];
int cnt_u[N];
std::vector<int> p_lca[N], lca_u[N], lca_p[N];
int t[N * 2];
int *T = t + N;
int ans[N];

int main () {
  int n, m;
  read(n), read(m);
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  for (int i = 1; i <= n; ++i) {
    read(w[i]);
  }
  for (int i = 1; i <= m; ++i) {
    read(u[i]), read(v[i]);
    qadd(u[i], v[i], i), qadd(v[i], u[i], i);
  }
  dep[1] = 1;
  tarjan(1);
  for (int i = 1; i <= m; ++i) {
    ++cnt_u[u[i]];
    p_lca[v[i]].push_back(dep[u[i]] - (dep[lca[i]] << 1));
    lca_u[lca[i]].push_back(dep[u[i]]);
    lca_p[lca[i]].push_back(dep[u[i]] - (dep[lca[i]] << 1));
  }
  dfs1(1, 0);
  dfs2(1, 0);
  for (int i = 1; i <= m; ++i) {
    if (dep[u[i]] == dep[lca[i]] + w[lca[i]]) {
      --ans[lca[i]];
    }
  }
  for (int i = 1; i <= n; ++i) {
    write(ans[i]), SP;
  }
  EL;
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
void qadd(int u, int v, int num) {
  qnxt[++qid] = qhed[u];
  qhed[u] = qid;
  qto[qid] = v;
  qnum[qid] = num;
}
int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void tarjan(int u) {
  fa[u] = u;
  for (int i = qhed[u]; i; i = qnxt[i]) {
    int v = qto[i];
    if (fa[v]) {
      lca[qnum[i]] = find(v);
    }
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!fa[v]) {
      dep[v] = dep[u] + 1;
      tarjan(v);
      fa[v] = u;
    }
  }
}
void dfs1(int u, int fa) {
  ans[u] -= T[w[u] + dep[u]];
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v ^ fa) {
      dfs1(v, u);
    }
  }
  T[dep[u]] += cnt_u[u];
  ans[u] += T[w[u] + dep[u]];
  for (auto i : lca_u[u]) {
    --T[i];
  }
}
void dfs2(int u, int fa) {
  ans[u] -= T[w[u] - dep[u]];
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v ^ fa) {
      dfs2(v, u);
    }
  }
  for (auto i : p_lca[u]) {
    ++T[i];
  }
  ans[u] += T[w[u] - dep[u]];
  for (auto i : lca_p[u]) {
    --T[i];
  }
}
