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
const int N = 5005;
const int M = 10005;

void add(int, int);
void getloop(int);
void dfs(int, int);
void update();

std::vector<int> edg[N];
int hed[N], nxt[M], to[M], id;
int loop[N], lops;
int fa[N];
int dfn[N], num;
int ans[N];
bool vis[N];
int now[N];
int cnt;
int delu, delv;
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    edg[u].push_back(v);
    edg[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    sort(edg[i].begin(), edg[i].end(), std::greater<int>());
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < (int)edg[i].size(); ++j) {
      add(i, edg[i][j]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    ans[i] = iinf;
  }
  if (m == n - 1) {
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
      write(now[i]), SP;
    }
    EL;
  } else {
    getloop(1);
    for (int i = 1; i < lops; ++i) {
      cnt = 0;
      delu = loop[i], delv = loop[i + 1];
      dfs(1, 0);
      update();
    }
    for (int i = 1; i <= n; ++i) {
      write(ans[i]), SP;
    }
    EL;
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
void getloop(int u) {
  dfn[u] = ++num;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa[u]) {
      continue;
    }
    if (dfn[v]) {
      if (dfn[v] < dfn[u]) {
        continue;
      }
      loop[lops = 1] = v;
      for (; v != u; v = fa[v]) {
        loop[++lops] = fa[v];
      }
    } else {
      fa[v] = u;
      getloop(v);
    }
  }
}
void dfs(int u, int fa) {
  now[++cnt] = u;
  vis[u] = true;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa || (u == delu && v == delv) || (u == delv && v == delu) || vis[v]) {
      continue;
    }
    dfs(v, u);
  }
  vis[u] = false;
}
void update() {
  for (int i = 1; i <= n; ++i) {
    if (now[i] > ans[i]) {
      return;
    } else {
      if (now[i] < ans[i]) {
        break;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    ans[i] = now[i];
  }
}
