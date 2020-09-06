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

const int N = 1005;
const int M = 100005;

void add(int u, int v);
int lca(int u, int v);
void blossom(int u, int v, int w);
int work(int u);

int vis[N];
int pre[N], match[N];
int dfn[N], cnt;
int fa[N];
std::queue<int> q;
int hed[N], nxt[M], to[M], id;
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (!match[i]) {
      ans += work(i);
    }
  }
  write(ans), EL;
  for (int i = 1; i <= n; ++i) {
    write(match[i]), SP;
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
int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int lca(int u, int v) {
  for (u = find(u), v = find(v), ++cnt; dfn[u] != cnt; ) {
    dfn[u] = cnt;
    u = find(pre[match[u]]);
    if (v) {
      std::swap(u, v);
    }
  }
  return u;
}
void blossom(int u, int v, int w) {
  while (find(u) != w) {
    pre[u] = v, v = match[u];
    if (vis[v] == 2) {
      vis[v] = 1;
      q.push(v);
    }
    if (find(u) == u) {
      fa[u] = w;
    }
    if (find(v) == v) {
      fa[v] = w;
    }
    u = pre[v];
  }
}
int work(int u) {
  while (!q.empty()) {
    q.pop();
  }
  for (int i = 1; i <= n; ++i) {
    vis[i] = pre[i] = 0;
    fa[i] = i;
  }
  q.push(u);
  vis[u] = 1;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = hed[x]; i; i = nxt[i]) {
      int y = to[i];
      if (vis[y] == 2 || find(x) == find(y)) {
        continue;
      }
      if (!vis[y]) {
        vis[y] = 2;
        pre[y] = x;
        if (!match[y]) {
          for (int now = y, las; now; now = las) {
            las = match[pre[now]];
            match[pre[now]] = now;
            match[now] = pre[now];
          }
          return true;
        } else {
          vis[match[y]] = 1;
          q.push(match[y]);
        }
      } else {
        int w = lca(x, y);
        blossom(x, y, w);
        blossom(y, x, w);
      }
    }
  }
  return false;
}
