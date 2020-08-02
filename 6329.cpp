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

const int N = 100005;
const int M = 200005;

void add(int, int);
int qry1(int, int);
int qry2(int, int);
void upd1(int, int, int);
void upd2(int, int, int);
void getrot(int, int);
void dfs(int, int);

int hed[N], nxt[M], to[M], id;
bool vis[N];
int siz[N];
int ssum, rot, mis, mxd;
int dep[N];
int fa[N];
int len[22][N];
std::vector<int> BIT1[N];
std::vector<int> BIT2[N];
int a[N];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  ssum = n;
  mis = iinf;
  getrot(1, 0);
  dfs(rot, 0);
  int lastans = 0;
  for (int i = 1; i <= m; ++i) {
    int type, x, y;
    read(type), read(x), read(y);
    x ^= lastans;
    y ^= lastans;
    if (type == 0) {
      int ans = qry1(x, y + 1);
      int lx = x, fx = fa[x];
      while (fx) {
        int dx = len[dep[fx]][x] - 1;
        if (dx > y) {
          lx = fx;
          fx = fa[fx];
          continue;
        }
        ans += qry1(fx, y + 1 - dx);
        ans -= qry2(lx, y + 1 - dx);
        lx = fx;
        fx = fa[fx];
        continue;
      }
      write(lastans = ans), EL;
    } else {
      int lx = x, fx = fa[x];
      upd1(x, 1, y - a[x]);
      while (fx) {
        int dx = len[dep[fx]][x];
        upd1(fx, dx, y - a[x]);
        upd2(lx, dx, y - a[x]);
        lx = fx;
        fx = fa[fx];
      }
      a[x] = y;
    }
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

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
int qry1(int root, int x) {
  int ans = 0;
  if (x >= BIT1[root].size()) {
    x = BIT1[root].size() - 1;
  }
  while (x) {
    ans += BIT1[root][x];
    x -= x & -x;
  }
  return ans;
}
int qry2(int root, int x) {
  int ans = 0;
  if (x >= BIT2[root].size()) {
    x = BIT2[root].size() - 1;
  }
  while (x) {
    ans += BIT2[root][x];
    x -= x & -x;
  }
  return ans;
}
void upd1(int root, int x, int num) {
  while (x < (int)BIT1[root].size()) {
    BIT1[root][x] += num;
    x += x & -x;
  }
}
void upd2(int root, int x, int num) {
  if (!x) {
    return;
  }
  while (x < (int)BIT2[root].size()) {
    BIT2[root][x] += num;
    x += x & -x;
  }
}
void init1(int root, int x) {
  for (int i = 0; i <= x; ++i) {
    BIT1[root].push_back(0);
  }
}
void init2(int root, int x) {
  for (int i = 0; i <= x; ++i) {
    BIT2[root].push_back(0);
  }
}
void calc1(int u, int fa, int length, int root) {
  len[dep[root]][u] = length;
  siz[u] = 1;
  mxd = max(mxd, length);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa && !vis[v]) {
      calc1(v, u, length + 1, root);
      siz[u] += siz[v];
    }
  }
}
void calc2(int u, int fat, int root) {
  upd1(root, len[dep[root]][u], a[u]);
  upd2(root, len[dep[fa[root]]][u], a[u]);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fat && !vis[v]) {
      calc2(v, u, root);
    }
  }
}
void getrot(int u, int fa) {
  siz[u] = 1;
  int ming = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa && !vis[v]) {
      getrot(v, u);
      siz[u] += siz[v];
      ming = max(ming, siz[v]);
    }
  }
  ming = max(ming, ssum - siz[u]);
  if (ming < mis) {
    mis = ming;
    rot = u;
  }
}
void dfs(int u, int lasmd) {
  vis[u] = true;
  mxd = 0;
  calc1(u, 0, 1, u);
  init1(u, mxd);
  init2(u, lasmd);
  calc2(u, 0, u);
  int tmp = mxd;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      ssum = siz[v];
      rot = 0;
      mis = iinf;
      getrot(v, u);
      fa[rot] = u;
      dep[rot] = dep[u] + 1;
      dfs(rot, tmp);
    }
  }
}
