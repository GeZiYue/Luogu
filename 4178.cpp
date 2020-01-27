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
const int N = 40005;
const int M = 80005;
const int Q = 20000;

void add(int, int, int);
void solve(int);

int hed[N], nxt[M], to[M], wei[M], id;
int dis[N], tot;
int siz[N], sum, rot, rots;
int BIT[Q + 5];
bool vis[N];
int qry;
ll ans;
int n;

int main () {
  read(n);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    add(u, v, w), add(v, u, w);
  }
  read(qry);
  solve(1);
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
  wei[id] = w;
}
void update(int x, int num) {
  while (x <= Q) {
    BIT[x] += num;
    x += x & -x;
  }
}
int query(int x) {
  int ans = 0;
  while (x) {
    ans += BIT[x];
    x -= x & -x;
  }
  return ans;
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
void getrot(int u, int fa) {
  int maxs = sum - siz[u];
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v] && v != fa) {
      getrot(v, u);
      maxs = max(maxs, siz[v]);
    }
  }
  if (maxs < rots) {
    rots = maxs;
    rot = u;
  }
}
void dfs(int u, int fa, int len) {
  if (len > qry) {
    return;
  }
  ++ans;
  ans += query(qry - len);
  dis[++tot] = len;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v] && v != fa) {
      dfs(v, u, len + wei[i]);
    }
  }
}
void calc(int u) {
  tot = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      int od = tot;
      dfs(v, u, wei[i]);
      for (int j = od + 1; j <= tot; ++j) {
        update(dis[j], 1);
      }
    }
  }
  for (int i = 1; i <= tot; ++i) {
    update(dis[i], -1);
  }
}
void solve(int u) {
  getsiz(u, 0);
  sum = siz[u], rot = 0, rots = iinf;
  getrot(u, 0);
  u = rot;
  vis[u] = true;
  calc(u);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      solve(v);
    }
  }
}
