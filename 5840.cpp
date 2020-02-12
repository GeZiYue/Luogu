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

const int S = 2000005;
const int N = 100005;
const int M = 26;

class Aho_Corasick_Automaton {
private:
  class Node {
  public:
    int to[26];
    int fail;
  };
  Node sta[S];
  int tot;
  int end[N];
public:
  Aho_Corasick_Automaton() : tot(1) {}
  void insert(char *, int);
  void build();
  friend void update(char *);
  friend int query(int);
} ACAM;

void update(char *);
int query(int);
int hed[S], nxt[S], to[S], id;
int dep[S], siz[S], fa[S], son[S], top[S], dfn[S], cnt;
int BIT[S];

int que[S], qhed, qtil;
int a[S], tot;
char s[S];
int n;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s);
    ACAM.insert(s, i);
  }
  ACAM.build();
  int m;
  read(m);
  while (m--) {
    int type;
    read(type);
    if (type == 1) {
      scanf("%s", s);
      update(s);
    } else {
      int x;
      read(x);
      write(query(x)), EL;
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

void Aho_Corasick_Automaton::insert(char *s, int num) {
  int len = strlen(s);
  int now = 1;
  for (int i = 0; i < len; ++i) {
    int &tmp = sta[now].to[s[i] - 'a'];
    now = tmp ? tmp : tmp = ++tot;
  }
  end[num] = now;
}
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs1(int u) {
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa[u]) {
      dep[v] = dep[u] + 1;
      fa[v] = u;
      dfs1(v);
      siz[u] += siz[v];
      if (siz[v] > siz[son[u]]) {
        son[u] = v;
      }
    }
  }
}
void dfs2(int u) {
  dfn[u] = ++cnt;
  if (son[u]) {
    top[son[u]] = top[u];
    dfs2(son[u]);
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa[u] && v != son[u]) {
      top[v] = v;
      dfs2(v);
    }
  }
}
void Aho_Corasick_Automaton::build() {
  qhed = 1, qtil = 0;
  for (int i = 0; i < 26; ++i) {
    if (sta[1].to[i]) {
      que[++qtil] = sta[1].to[i];
      sta[sta[1].to[i]].fail = 1;
    } else {
      sta[1].to[i] = 1;
    }
  }
  while (qhed <= qtil) {
    int u = que[qhed++];
    add(sta[u].fail, u);
    for (int i = 0; i < 26; ++i) {
      int &tmp = sta[u].to[i];
      if (tmp) {
        sta[tmp].fail = sta[sta[u].fail].to[i];
        que[++qtil] = tmp;
      } else {
        tmp = sta[sta[u].fail].to[i];
      }
    }
  }
  dfs1(1);
  top[1] = 1;
  dfs2(1);
}
int lca(int x, int y) {
  while (top[x] ^ top[y]) {
    if (dep[top[x]] < dep[top[y]]) {
      y = fa[top[y]];
    } else {
      x = fa[top[x]];
    }
  }
  return dep[x] < dep[y] ? x : y;
}
void BIT_update(int x, int num) {
  while (x <= cnt) {
    BIT[x] += num;
    x += x & -x;
  }
}
int BIT_query(int x) {
  int ans = 0;
  while (x) {
    ans += BIT[x];
    x -= x & -x;
  }
  return ans;
}
bool cmp(int i, int j) {
  return dfn[i] < dfn[j];
}
void update(char *s) {
  int len = strlen(s);
  int now = 1;
  tot = 0;
  for (int i = 0; i < len; ++i) {
    now = ACAM.sta[now].to[s[i] - 'a'];
    a[++tot] = now;
  }
  sort(a + 1, a + tot + 1, cmp);
  tot = std::unique(a + 1, a + tot + 1) - a - 1;
  BIT_update(dfn[a[1]], 1);
  for (int i = 2; i <= tot; ++i) {
    BIT_update(dfn[a[i]], 1);
    BIT_update(dfn[lca(a[i - 1], a[i])], -1);
  }
}
int query(int x) {
  int u = ACAM.end[x];
  return BIT_query(dfn[u] + siz[u] - 1) - BIT_query(dfn[u] - 1);
}
