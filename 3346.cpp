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
const int K = 2000005;

class Trie {
private:
  class Node {
  public:
    int to[10];
  };
  Node tre[K];
  int tot;
public:
  Trie() : tot(1) {}
  void dfs(int, int, int);
  friend class Wide_Suffix_Automaton;
};
class Wide_Suffix_Automaton {
private:
  class Node {
  public:
    int to[10];
    int len, lnk;
    Node(int ln = 0, int lk = 0) : len(ln), lnk(lk) {
      memset(to, 0, sizeof(to));
    }
  };
  Node sta[K << 1];
  int tot;
  int extend(int, int);
public:
  Wide_Suffix_Automaton() : tot(1) {}
  void build(const Trie &);
  ll query();
};

void add(int, int);

Trie TRIE;
Wide_Suffix_Automaton WSAM;
int hed[N], nxt[M], to[M], id;
int col[N];
int deg[N];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(col[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
    ++deg[u], ++deg[v];
  }
  for (int i = 1; i <= n; ++i) {
    if (deg[i] == 1) {
      TRIE.dfs(i, 0, 1);
    }
  }
  WSAM.build(TRIE);
  write(WSAM.query()), EL;
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
void Trie::dfs(int u, int fa, int fn) {
  int &tmp = tre[fn].to[col[u]];
  int now = tmp ? tmp : tmp = ++tot;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa) {
      dfs(v, u, now);
    }
  }
}
int Wide_Suffix_Automaton::extend(int c, int las) {
  int cur = ++tot;
  sta[cur].len = sta[las].len + 1;
  int p = las;
  while (p && !sta[p].to[c]) {
    sta[p].to[c] = cur;
    p = sta[p].lnk;
  }
  if (p) {
    int q = sta[p].to[c];
    if (sta[p].len + 1 == sta[q].len) {
      sta[cur].lnk = q;
    } else {
      int cl = ++tot;
      sta[cl].len = sta[p].len + 1;
      sta[cl].lnk = sta[q].lnk;
      memcpy(sta[cl].to, sta[q].to, sizeof(sta[cl].to));
      while (p && sta[p].to[c] == q) {
        sta[p].to[c] = cl;
        p = sta[p].lnk;
      }
      sta[cur].lnk = sta[q].lnk = cl;
    }
  } else {
    sta[cur].lnk = 1;
  }
  return cur;
}
void Wide_Suffix_Automaton::build(const Trie &trie) {
  std::queue<pii> q;
  q.push(pii(1, 1));
  while (!q.empty()) {
    int u = q.front().first, las = q.front().second;
    q.pop();
    for (int i = 0; i < m; ++i) {
      int v = trie.tre[u].to[i];
      if (v) {
        int tmp = extend(i, las);
        q.push(pii(v, tmp));
      }
    }
  }
}
ll Wide_Suffix_Automaton::query() {
  ll ans = 0;
  for (int i = 2; i <= tot; ++i) {
    ans += sta[i].len - sta[sta[i].lnk].len;
  }
  return ans;
}
