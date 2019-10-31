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

void add(int, int, int);
void qadd(int, int);
void tarjan(int);
bool check(int);

int hed[N], nxt[M], to[M], dis[M], id;
int qhed[N], qnxt[M], qto[M], qid = 1;
int u[N], v[N], lca[N];
int lenq[N];
int len[N];
int ffa[N];
int sum[N];
int fa[N];
int maxdis, maxlen;
int n, m;
int cnt;

int main () {
  read(n), read(m);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    add(u, v, w), add(v, u, w);
  }
  for (int i = 1; i <= m; ++i) {
    read(u[i]), read(v[i]);
    qadd(u[i], v[i]), qadd(v[i], u[i]);
  }
  tarjan(1);
  for (int i = 1; i <= m; ++i) {
    lenq[i] = len[u[i]] + len[v[i]] - (len[lca[i]] << 1);
    maxlen = max(maxlen, lenq[i]);
  }
  int l = 0, r = maxlen;
  int ans = -1;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
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

void add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
void qadd(int u, int v) {
  qnxt[++qid] = qhed[u];
  qhed[u] = qid;
  qto[qid] = v;
}
int find(int x) {
  return ffa[x] == x ? x : ffa[x] = find(ffa[x]);
}
void tarjan(int u) {
  ffa[u] = u;
  for (int i = qhed[u]; i; i = qnxt[i]) {
    int v = qto[i];
    if (ffa[v]) {
      lca[i >> 1] = find(v);
    }
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!ffa[v]) {
      fa[v] = u;
      len[v] = len[u] + dis[i];
      tarjan(v);
      ffa[v] = u;
    }
  }
}
void dfs(int u) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v ^ fa[u]) {
      dfs(v);
      sum[u] += sum[v];
      if (sum[v] == cnt) {
        maxdis = max(maxdis, dis[i]);
      }
    }
  }
}
bool check(int x) {
  memset(sum, 0, sizeof(sum));
  cnt = 0;
  for (int i = 1; i<= m; ++i) {
    if (lenq[i] > x) {
      ++sum[u[i]], ++sum[v[i]];
      sum[lca[i]] -= 2;
      ++cnt;
    }
  }
  maxdis = 0;
  dfs(1);
  return maxlen - maxdis <= x;
}
