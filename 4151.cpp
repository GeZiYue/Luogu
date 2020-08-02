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
using std::sort;

const int N = 50005;
const int M = 200005;

void add(int, int, ll);
void dfs(int, ll);
void insert(ll);
ll query(ll);

int hed[N], nxt[M], to[M], id;
ll dis[M];
bool vis[N];
ll w[N];
ll v[65];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    ll w;
    read(u), read(v), read(w);
    add(u, v, w), add(v, u, w);
  }
  dfs(1, 0);
  write(query(w[n])), EL;
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

void add(int u, int v, ll w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
void dfs(int u, ll res) {
  w[u] = res;
  vis[u] = true;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      dfs(v, res ^ dis[i]);
    } else {
      insert(res ^ dis[i] ^ w[v]);
    }
  }
}
void insert(ll x) {
  for (int i = 60; i >= 0; --i) {
    if (x & (1ll << i)) {
      if (!v[i]) {
        v[i] = x;
        break;
      } else {
        x ^= v[i];
      }
    }
  }
}
ll query(ll x) {
  for (int i = 60; i >= 0; --i) {
    if ((x ^ v[i]) > x) {
      x ^= v[i];
    }
  }
  return x;
}
