#include <unordered_set>
#include <unordered_map>
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
const int N = 10005;
const int M = 20005;
const int K = 105;

void add(int, int, int);
void getsiz(int, int);
void getrt(int, int);
void dfs(int);

int siz[N];
int len[N];
bool vis[N];
int cnt[N];
int hed[N], nxt[M], to[M], dis[M], id;
int sum, root, weight;
int query[K];
bool ans[K];
bool exi[10000005];
int sta[N], top;
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i < n; ++i) {
    int u, v, diss;
    read(u), read(v), read(diss);
    add(u, v, diss), add(v, u, diss);
  }
  for (int i = 1; i <= m; ++i) {
    read(query[i]);
  }
  getsiz(1, 0);
  sum = siz[1];
  root = 0;
  weight = iinf;
  getrt(1, 0);
  dfs(root);
  for (int i = 1; i <= m; ++i) {
    puts(ans[i] ? "AYE" : "NAY");
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

void add(int u, int v, int diss) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = diss;
}
void getsiz(int u, int fa) {
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v] && v != fa) {
      getsiz(v, u);
      siz[u] += siz[v];
    }
  }
}
void getrt(int u, int fa) {
  int maxx = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v] && v != fa) {
      getrt(v, u);
      maxx = max(maxx, siz[v]);
    }
  }
  maxx = max(maxx, sum - siz[u]);
  if (maxx < weight) {
    weight = maxx;
    root = u;
  }
}
void getdis(int u, int fa, int now) {
  len[++len[0]] = now;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v] && v != fa) {
      getdis(v, u, now + dis[i]);
    }
  }
}
void calc(int u) {
  top = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      len[0] = 0;
      getdis(v, u, dis[i]);
      for (int j = 1; j <= len[0]; ++j) {
        for (int k = 1; k <= m; ++k) {
          if (query[k] >= len[j]) {
            ans[k] |= exi[query[k] - len[j]];
          }
        }
      }
      for (int j = 1; j <= len[0]; ++j) {
        exi[sta[++top] = len[j]] = true;
      }
    }
  }
  for (int i = 1; i <= top; ++i) {
    exi[sta[i]] = false;
  }
}
void dfs(int u) {
  vis[u] = true;
  exi[0] = true;
  calc(u);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      getsiz(v, u);
      sum = siz[v];
      root = 0;
      weight = iinf;
      getrt(v, u);
      dfs(root);
    }
  }
}
