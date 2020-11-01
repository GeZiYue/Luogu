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
#include <unordered_set>
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

const int N = 30005;
const int M = 60005;

void add(int u, int v);
void getsiz(int u, int fa);
void getrot(int u, int fa);
void getp(int u, int fa, int len);
void solve(int u);
void dfs(int u);

int hed[N], nxt[M], to[M], id;
int siz[N];
int asz, nsz, rot;
int dis[N], tot;
bool vis[N];
int val[N], sg[N];
bool ans;
int n;

int main() {
  int T;
  read(T);
  while (T--) {
    memset(hed, 0, sizeof(hed));
    id = 0;
    ans = false;
    memset(vis, false, sizeof(vis));
    read(n);
    for (int i = 1; i < n; ++i) {
      int u, v;
      read(u), read(v);
      add(u, v), add(v, u);
    }
    for (int i = 1; i <= n; ++i) {
      read(val[i]);
    }
    int k;
    read(k);
    if (k == 1) {
      for (int i = 1; i <= n; ++i) {
        sg[i] = val[i];
      }
    }
    if (k == 2) {
      int s;
      read(s);
      for (int i = 1; i <= n; ++i) {
        if (val[i] % (s + 1) == s) {
          sg[i] = 2;
        } else {
          sg[i] = val[i] % (s + 1) % 2;
        }
      }
    }
    if (k == 3) {
      int s;
      read(s);
      for (int i = 1; i <= n; ++i) {
        sg[i] = val[i] / s;
      }
    }
    if (k == 4) {
      for (int i = 1; i <= n; ++i) {
        if (!val[i]) {
          sg[i] = 0;
        } else {
          if (val[i] % 4 == 0) {
            sg[i] = val[i] - 1;
          } else {
            if (val[i] % 4 == 3) {
              sg[i] = val[i] + 1;
            } else {
              sg[i] = val[i];
            }
          }
        }
      }
    }
    getsiz(1, 0);
    asz = siz[1];
    nsz = iinf;
    rot = 0;
    getrot(1, 0);
    dfs(rot);
    if (ans) {
      puts("Mutalisk ride face how to lose?");
    } else {
      puts("The commentary cannot go on!");
    }
  }
  return 0;
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

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void getsiz(int u, int fa) {
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa && !vis[v]) {
      getsiz(v, u);
      siz[u] += siz[v];
    }
  }
}
void getrot(int u, int fa) {
  int maxi = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa && !vis[v]) {
      getrot(v, u);
      maxi = max(maxi, siz[v]);
    }
  }
  maxi = max(maxi, asz - siz[u]);
  if (maxi < nsz) {
    nsz = maxi;
    rot = u;
  }
}
void getp(int u, int fa, int len) {
  len ^= sg[u];
  dis[++tot] = len;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa && !vis[v]) {
      getp(v, u, len);
    }
  }
}
void solve(int u) {
  if (!sg[u]) {
    ans = true;
  }
  if (ans) {
    return;
  }
  std::unordered_set<int> S;
  S.insert(sg[u]);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      tot = 0;
      getp(v, u, 0);
      for (int j = 1; j <= tot; ++j) {
        if (S.count(dis[j])) {
          ans = true;
          return;
        }
      }
      for (int j = 1; j <= tot; ++j) {
        S.insert(dis[j] ^ sg[u]);
      }
    }
  }
}
void dfs(int u) {
  vis[u] = true;
  solve(u);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (!vis[v]) {
      getsiz(v, u);
      asz = siz[v];
      nsz = iinf;
      rot = 0;
      getrot(v, u);
      dfs(rot);
    }
  }
}
