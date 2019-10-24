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
const int N = 20005;
const int M = 40005;

void add(int, int, int);
void getsiz(int, int);
void getrt(int, int);
void dfs(int);
int gcd(int, int);

int hed[N], nxt[M], to[M], dis[M], id;
int siz[N];
int sum, root, weight;
bool vis[N];
int len[3];
int cnt[3];
int ans;

int main () {
  int n;
  read(n);
  for (int i = 1; i < n; ++i) {
    int u, v, diss;
    read(u), read(v), read(diss);
    add(u, v, diss), add(v, u, diss);
  }
  getsiz(1, 0);
  sum = siz[1];
  root = 0;
  weight = iinf;
  getrt(1, 0);
  dfs(root);
  ans = (ans << 1) + n;
  int now = n * n;
  int k = gcd(ans, now);
  ans /= k, now /= k;
  write(ans), putchar('/'), write(now), EL;
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
  int now = sum - siz[u];
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v] && v != fa) {
      getrt(v, u);
      now = max(now, siz[v]);
    }
  }
  if (now < weight) {
    weight = now;
    root = u;
  }
}
void getlen(int u, int fa, int now) {
  ++len[now];
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v] && v != fa) {
      getlen(v, u, (now + dis[i]) % 3);
    }
  }
}
void calc(int u) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      len[0] = len[1] = len[2] = 0;
      getlen(v, u, dis[i] % 3);
      ans += len[0] * cnt[0] + len[1] * cnt[2] + len[2] * cnt[1];
      cnt[0] += len[0];
      cnt[1] += len[1];
      cnt[2] += len[2];
    }
  }
}
void dfs(int u) {
  vis[u] = true;
  cnt[0] = 1;
  cnt[1] = cnt[2] = 0;
  calc(u);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      getsiz(v, 0);
      sum = siz[v];
      root = 0;
      weight = iinf;
      getrt(v, 0);
      dfs(root);
    }
  }
}
int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}
