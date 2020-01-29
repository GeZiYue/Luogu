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
const int N = 500002;

class SAM {
private:
  class Node {
  public:
    int to[26], len, lnk;
  };
  Node tre[N << 1];
  int las, siz;
  int hed[N << 1], nxt[N << 1], to[N << 1], id;
  int f[N << 1], g[N << 1];
  int vis[N << 1];
  void add(int, int);
  void dfs1(int);
  void dfs2(int);
  void dfs3(int, int);
public:
  SAM() { tre[0].lnk = -1; }
  void extend(int);
  void solve(int, int);
};

SAM sam;
char ch[N];
int n;
int type, k;

int main () {
  scanf("%s", ch + 1);
  n = strlen(ch + 1);
  read(type), read(k);
  for (int i = 1; i <= n; ++i) {
    sam.extend(ch[i] - 'a');
  }
  sam.solve(type, k);
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

void SAM::extend(int c) {
  int cur = ++siz;
  tre[cur].len = tre[las].len + 1;
  f[cur] = 1;
  int p = las;
  while (~p && !tre[p].to[c]) {
    tre[p].to[c] = cur;
    p = tre[p].lnk;
  }
  if (~p) {
    int q = tre[p].to[c];
    if (tre[q].len == tre[p].len + 1) {
      tre[cur].lnk = q;
    } else {
      int cl = ++siz;
      tre[cl].lnk = tre[q].lnk;
      tre[cl].len = tre[p].len + 1;
      memcpy(tre[cl].to, tre[q].to, sizeof(int) * 26);
      while (~p && tre[p].to[c] == q) {
        tre[p].to[c] = cl;
        p = tre[p].lnk;
      }
      tre[q].lnk = tre[cur].lnk = cl;
    }
  } else {
    tre[cur].lnk = 0;
  }
  las = cur;
}
void SAM::add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void SAM::dfs1(int u) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    dfs1(v);
    f[u] += f[v];
  }
}
void SAM::dfs2(int u) {
  if (vis[u]) {
    return;
  }
  vis[u] = true;
  for (int i = 0; i < 26; ++i) {
    int v = tre[u].to[i];
    if (v) {
      dfs2(v);
      g[u] += g[v];
    }
  }
}
void SAM::dfs3(int u, int k) {
  if (k <= f[u]) {
    return;
  }
  k -= f[u];
  for (int i = 0; i < 26; ++i) {
    int v = tre[u].to[i];
    if (v) {
      if (k > g[v]) {
        k -= g[v];
      } else {
        putchar(i + 'a');
        dfs3(v, k);
        return;
      }
    }
  }
}
void SAM::solve(int ty, int k) {
  for (int i = 1; i <= siz; ++i) {
    add(tre[i].lnk, i);
  }
  if (ty) {
    dfs1(0);
    f[0] = 0;
    for (int i = 1; i <= siz; ++i) {
      g[i] = f[i];
    }
  } else {
    for (int i = 1; i <= siz; ++i) {
      g[i] = f[i] = 1;
    }
  }
  dfs2(0);
  if (k > g[0]) {
    puts("-1");
    return;
  }
  dfs3(0, k);
  EL;
}
