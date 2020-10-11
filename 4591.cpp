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

const int N = 10005;
const int Mod = 1000000007;

class Suffix_Automaton {
public:
  class Node {
  public:
    int lnk, siz, len, to[26];
  };
  Node tre[N << 1];
  int hed[N << 1], nxt[N << 1], to[N << 1], id;
  int las, tot;
  Suffix_Automaton() { tre[0].lnk = -1; }
  void extend(int c);
  void add(int u, int v);
  void dfs(int u);
} SAM;

int find(int k, int len);
void add(int &a, int b) {
  a += b;
  if (a >= Mod) {
    a -= Mod;
  }
}

char ch[N];
int dp[2][N << 1];
int n, m;

int main() {
  read(n);
  scanf("%s", ch + 1);
  m = strlen(ch + 1);
  for (int i = 1; i <= m; ++i) {
    SAM.extend(ch[i] - 'A');
  }
  for (int i = 1; i <= SAM.tot; ++i) {
    SAM.add(SAM.tre[i].lnk, i);
  }
  SAM.dfs(0);
  dp[0][0] = 1;
  int las = 0, now = 1;
  for (int i = 1; i <= n; ++i) {
    int k;
    read(k);
    for (int j = 0; j <= SAM.tot; ++j) {
      dp[now][j] = 0;
    }
    for (int j = 1; j <= k; ++j) {
      scanf("%s", ch + 1);
      int len = strlen(ch + 1);
      for (int l = 0; l <= SAM.tot; ++l) {
        int tmp = find(l, len);
        if (tmp) {
          add(dp[now][tmp], dp[las][l]);
        }
      }
    }
    las ^= 1;
    now ^= 1;
  }
  int ans = 0;
  for (int i = 1; i <= SAM.tot; ++i) {
    add(ans, dp[las][i] * 1ll * SAM.tre[i].siz % Mod);
  }
  write(ans), EL;
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

void Suffix_Automaton::extend(int c) {
  int p = las;
  int now = ++tot;
  tre[now].len = tre[tot].len + 1;
  tre[now].siz = 1;
  while (~p && !tre[p].to[c]) {
    tre[p].to[c] = now;
    p = tre[p].lnk;
  }
  if (p == -1) {
    tre[now].lnk = 0;
  } else {
    int q = tre[p].to[c];
    if (tre[p].len + 1 == tre[q].len) {
      tre[now].lnk = q;
    } else {
      int cur = ++tot;
      tre[cur].len = tre[p].len + 1;
      tre[cur].lnk = tre[q].lnk;
      std::copy(tre[q].to, tre[q].to + 26, tre[cur].to);
      while (~p && tre[p].to[c] == q) {
        tre[p].to[c] = cur;
        p = tre[p].lnk;
      }
      tre[q].lnk = tre[now].lnk = cur;
    }
  }
  las = now;
}
void Suffix_Automaton::add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void Suffix_Automaton::dfs(int u) {
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    dfs(v);
    tre[u].siz += tre[v].siz;
  }
}
int find(int k, int len) {
  for (int i = 1; i <= len; ++i) {
    k = SAM.tre[k].to[ch[i] - 'A'];
    if (!k) {
      return 0;
    }
  }
  return k;
}
