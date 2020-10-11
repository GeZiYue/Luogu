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

template <class T> void read(T &);
template <class T> void write(const T &);

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

const int N = 200005;

class Suffix_Automaton {
public:
  class Node {
  public:
    int len, lnk;
    int to[26];
  };
  Node tre[N << 1];
  int hed[N << 1], nxt[N << 1], to[N << 1], id;
  int dep[N << 1], siz[N << 1], fa[N << 1], son[N << 1], top[N << 1];
  int tot, las;
  void clear();
  void extend(int c);
  void add(int u, int v);
  void dfs1(int u);
  void dfs2(int u);
  void build();
  int LCS(int u, int v);
} SAM, rSAM;

char ch[N];
int p[N], rp[N];
int Ls[N], Rs[N];
int n;

int main() {
  int T;
  read(T);
  while (T--) {
    SAM.clear(), rSAM.clear();
    memset(Ls, 0, sizeof(Ls));
    memset(Rs, 0, sizeof(Rs));
    scanf("%s", ch + 1);
    n = strlen(ch + 1);
    for (int i = 1; i <= n; ++i) {
      SAM.extend(ch[i] - 'a');
      p[i] = SAM.las;
    }
    for (int i = n; i >= 1; --i) {
      rSAM.extend(ch[i] - 'a');
      rp[i] = rSAM.las;
    }
    SAM.build(), rSAM.build();
    for (int l = 1; l <= n / 2; ++l) {
      for (int i = l, j = l * 2; j <= n; i += l, j += l) {
        int x = min(SAM.LCS(p[i], p[j]), l), y = min(rSAM.LCS(rp[i], rp[j]), l);
        if (x + y - 1 < l) {
          continue;
        }
        ++Ls[j + l - x], --Ls[j + y];
        ++Rs[i - x + 1], --Rs[i - (l - y) + 1];
      }
    }
    for (int i = 1; i <= n; ++i) {
      Ls[i] += Ls[i - 1];
      Rs[i] += Rs[i - 1];
    }
    ll ans = 0;
    for (int i = 2; i < n; ++i) {
      ans += Ls[i] * 1ll * Rs[i + 1];
    }
    write(ans), EL;
  }
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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

void Suffix_Automaton::clear() {
  tot = las = 1;
  memset(tre, 0, sizeof(tre));
  memset(son, 0, sizeof(son));
  memset(hed, 0, sizeof(hed));
  memset(siz, 0, sizeof(siz));
  memset(son, 0, sizeof(son));
  id = 0;
}
void Suffix_Automaton::extend(int c) {
  int now = ++tot;
  tre[now].len = tre[las].len + 1;
  int p = las;
  while (p && !tre[p].to[c]) {
    tre[p].to[c] = now;
    p = tre[p].lnk;
  }
  las = now;
  if (!p) {
    tre[now].lnk = 1;
  } else {
    int q = tre[p].to[c];
    if (tre[q].len == tre[p].len + 1) {
      tre[now].lnk = q;
    } else {
      int cur = ++tot;
      tre[cur].lnk = tre[q].lnk;
      tre[cur].len = tre[p].len + 1;
      std::copy(tre[q].to, tre[q].to + 26, tre[cur].to);
      while (p && tre[p].to[c] == q) {
        tre[p].to[c] = cur;
        p = tre[p].lnk;
      }
      tre[now].lnk = tre[q].lnk = cur;
    }
  }
}
void Suffix_Automaton::add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void Suffix_Automaton::dfs1(int u) {
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    dep[v] = dep[u] + 1;
    fa[v] = u;
    dfs1(v);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
}
void Suffix_Automaton::dfs2(int u) {
  if (son[u]) {
    top[son[u]] = top[u];
    dfs2(son[u]);
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != son[u]) {
      top[v] = v;
      dfs2(v);
    }
  }
}
void Suffix_Automaton::build() {
  for (int i = 2; i <= tot; ++i) {
    add(tre[i].lnk, i);
  }
  dfs1(1);
  top[1] = 1;
  dfs2(1);
}
int Suffix_Automaton::LCS(int u, int v) {
  while (top[u] != top[v]) {
    if (!v) {
      exit(0);
    }
    if (dep[top[u]] > dep[top[v]]) {
      u = fa[top[u]];
    } else {
      v = fa[top[v]];
    }
  }
  return dep[u] > dep[v] ? tre[v].len : tre[u].len;
}
