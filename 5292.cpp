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
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

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
using std::sort;

constexpr int N = 5005;
constexpr int M = 500005;

int find(int x);
void add(int u, int v);
void dfs(int u);

int hed[N], nxt[N << 2], to[N << 2], id;
std::vector<int> G[N];
bool val[N];
char ch[N];
int fa[N];
int col[N];
bool vis[N][N];
bool chk;
std::queue<pii> Q;
int n, m, q;

int main() {
  read(n), read(m), read(q);
  scanf("%s", ch + 1);
  for (int i = 1; i <= n; ++i) {
    val[i] = (ch[i] == '1');
    fa[i] = i;
    col[i] = -1;
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    if (val[u] == val[v]) {
      G[u].push_back(v), G[v].push_back(u);
    } else {
      if (find(u) ^ find(v)) {
        add(u, v), add(v, u);
        fa[find(u)] = find(v);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (col[i] == -1) {
      col[i] = 0;
      chk = true;
      dfs(i);
      if (!chk) {
        add(i, i);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    vis[i][i] = true;
    Q.emplace(i, i);
  }
  while (!Q.empty()) {
    int u, v;
    std::tie(u, v) = Q.front();
    Q.pop();
    for (int i = hed[u]; i; i = nxt[i]) {
      int u1 = to[i];
      for (int j = hed[v]; j; j = nxt[j]) {
        int v1 = to[j];
        if (vis[u1][v1]) {
          continue;
        }
        if (val[u1] != val[v1]) {
          continue;
        }
        vis[u1][v1] = vis[v1][u1] = true;
        Q.emplace(u1, v1);
      }
    }
  }
  while (q--) {
    int u, v;
    read(u), read(v);
    puts(vis[u][v] ? "YES" : "NO");
  }
  return 0;
}

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs(int u) {
  for (int v : G[u]) {
    if (col[v] == -1) {
      col[v] = col[u] ^ 1;
      add(u, v), add(v, u);
      Q.emplace(u, v);
      vis[u][v] = vis[v][u] = true;
      dfs(v);
    } else {
      if (col[v] == col[u]) {
        chk = false;
      }
    }
  }
}

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
