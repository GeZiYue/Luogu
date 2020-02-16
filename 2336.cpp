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

const int S = 100005;
const int N = 50005;
const int M = 100005;

class Aho_Corasick_Automaton {
private:
  class Node {
  public:
    std::map<int, int> to;
    int fail;
  };
  Node sta[S];
  int tot;
  int num, end[M];
public:
  Aho_Corasick_Automaton() : tot(1) {}
  void insert(std::vector<int>);
  void build();
  friend int query(std::vector<int>);
  friend void calc();
} ACAM;

int query(std::vector<int>);
void calc();
int hed[S], nxt[S], to[S], id;
int fa[S], dep[S], siz[S], sur[S], sum[S], son[S], top[S], ttl[S], ltt[S], cnt;
int ans1[M], ans2[N];
std::vector<int> a[N];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    int l1;
    read(l1);
    for (int j = 1; j <= l1; ++j) {
      int tmp;
      read(tmp);
      a[i].push_back(tmp);
    }
    a[i].push_back(10001);
    int l2;
    read(l2);
    for (int j = 1; j <= l2; ++j) {
      int tmp;
      read(tmp);
      a[i].push_back(tmp);
    }
  }
  for (int i = 1; i <= m; ++i) {
    int l;
    read(l);
    std::vector<int> b;
    for (int j = 1; j <= l; ++j) {
      int tmp;
      read(tmp);
      b.push_back(tmp);
    }
    ACAM.insert(b);
  }
  ACAM.build();
  for (int i = 1; i <= n; ++i) {
    ans2[i] = query(a[i]);
  }
  calc();
  for (int i = 1; i <= m; ++i) {
    write(ans1[i]), EL;
  }
  for (int i = 1; i <= n; ++i) {
    write(ans2[i]), SP;
  }
  EL;
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

void Aho_Corasick_Automaton::insert(std::vector<int> s) {
  int now = 1;
  int len = s.size();
  for (int i = 0; i < len; ++i) {
    if (sta[now].to.count(s[i])) {
      now = sta[now].to[s[i]];
    } else {
      now = sta[now].to[s[i]] = ++tot;
    }
  }
  end[++num] = now;
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
      fa[v] = u;
      dep[v] = dep[u] + 1;
      sur[v] += sur[u];
      dfs1(v);
      siz[u] += siz[v];
      if (siz[v] > siz[son[u]]) {
        son[u] = v;
      }
    }
  }
}
void dfs2(int u) {
  ttl[u] = ++cnt;
  ltt[cnt] = u;
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
  std::queue<int> q;
  for (auto i : sta[1].to) {
    q.push(i.second);
    sta[i.second].fail = 1;
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    add(sta[u].fail, u);
    for (auto i : sta[u].to) {
      int v = sta[u].fail;
      while (v != 1 && !sta[v].to.count(i.first)) {
        v = sta[v].fail;
      }
      if (sta[v].to.count(i.first)) {
        sta[i.second].fail = sta[v].to[i.first];
      } else {
        sta[i.second].fail = 1;
      }
      q.push(i.second);
    }
  }
  for (int i = 1; i <= num; ++i) {
    ++sur[end[i]];
  }
  dfs1(1);
  top[1] = 1;
  dfs2(1);
}
bool cmp(int i, int j) {
  return ttl[i] < ttl[j];
}
int lca(int u, int v) {
  while (top[u] ^ top[v]) {
    if (dep[top[u]] < dep[top[v]]) {
      v = fa[top[v]];
    } else {
      u = fa[top[u]];
    }
  }
  return dep[u] < dep[v] ? u : v;
}
int query(std::vector<int> s) {
  int len = s.size();
  std::vector<int> a;
  int now = 1;
  for (int i = 0; i < len; ++i) {
    while (now != 1 && !ACAM.sta[now].to.count(s[i])) {
      now = ACAM.sta[now].fail;
    }
    if (ACAM.sta[now].to.count(s[i])) {
      now = ACAM.sta[now].to[s[i]];
      a.push_back(now);
    } else {
      now = 1;
    }
  }
  sort(a.begin(), a.end(), cmp);
  a.erase(std::unique(a.begin(), a.end()), a.end());
  int ans = 0;
  int as = a.size();
  if (as) {
    ans += sur[a[0]];
    ++sum[a[0]];
    for (int i = 1; i < as; ++i) {
      ans += sur[a[i]];
      ++sum[a[i]];
      int LCA = lca(a[i - 1], a[i]);
      ans -= sur[LCA];
      --sum[LCA];
    }
  }
  return ans;
}
void calc() {
  for (int i = cnt; i >= 1; --i) {
    int u = ltt[i];
    for (int i = hed[u]; i; i = nxt[i]) {
      sum[u] += sum[to[i]];
    }
  }
  for (int i = 1; i <= ACAM.num; ++i) {
    ans1[i] = sum[ACAM.end[i]];
  }
}
