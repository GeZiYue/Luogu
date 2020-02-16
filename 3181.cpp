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

const int N = 200005;

class Suffix_Automaton {
private:
  class Node {
  public:
    int to[26];
    int len;
    int lnk;
    int sum;
    Node() {
      memset(to, 0, sizeof(to));
    }
  };
  Node sta[N << 1];
  int tot, las;
  int hed[N << 1], nxt[N << 1], to[N << 1], id;
  void add(int, int);
  void dfs(int);
public:
  Suffix_Automaton() : tot(1), las(1) { sta[1].lnk = 0; }
  void extend(int);
  void getsum();
  friend ll bfs(const Suffix_Automaton &, const Suffix_Automaton &);
} SAM1, SAM2;

char ch[N];

int main () {
  scanf("%s", ch + 1);
  int l1 = strlen(ch + 1);
  for (int i = 1; i <= l1; ++i) {
    SAM1.extend(ch[i] - 'a');
  }
  scanf("%s", ch + 1);
  int l2 = strlen(ch + 1);
  for (int i = 1; i <= l2; ++i) {
    SAM2.extend(ch[i] - 'a');
  }
  SAM1.getsum(), SAM2.getsum();
  write(bfs(SAM1, SAM2)), EL;
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

void Suffix_Automaton::extend(int c) {
  int cur = ++tot;
  sta[cur].len = sta[las].len + 1;
  sta[cur].sum = 1;
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
      memcpy(sta[cl].to, sta[q].to, sizeof(sta[q].to));
      while (p && sta[p].to[c] == q) {
        sta[p].to[c] = cl;
        p = sta[p].lnk;
      }
      sta[cur].lnk = sta[q].lnk = cl;
    }
  } else {
    sta[cur].lnk = 1;
  }
  las = cur;
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
    sta[u].sum += sta[v].sum;
  }
}
void Suffix_Automaton::getsum() {
  for (int i = 2; i <= tot; ++i) {
    add(sta[i].lnk, i);
  }
  dfs(1);
}
ll bfs(const Suffix_Automaton &SAM1, const Suffix_Automaton &SAM2) {
  std::queue<pii> q;
  q.push(pii(1, 1));
  ll ans = 0;
  while (!q.empty()) {
    int u1 = q.front().first, u2 = q.front().second;
    q.pop();
    for (int i = 0; i < 26; ++i) {
      int v1 = SAM1.sta[u1].to[i], v2 = SAM2.sta[u2].to[i];
      if (v1 && v2) {
        ans += SAM1.sta[v1].sum * 1ll * SAM2.sta[v2].sum;
        q.push(pii(v1, v2));
      }
    }
  }
  return ans;
}
