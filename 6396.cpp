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

const int Si = 100005;
const int N = 500005;
const int M = 2000005;

class PAM {
 public:
  class Node {
   public:
    int to[55];
    int len, lnk, par;
    Node(int ln = 0, int lk = 0) : len(ln), lnk(lk) {}
  };
  Node tre[Si];
  short S[Si];
  int len, tot, las;
  PAM() : len(0), tot(1), las(0) { S[0] = 52, tre[0] = Node(0, 1), tre[1] = Node(-1, 0); }
  int getfail(int las);
  void extend(short c);
} P;
namespace Graph {
int hed[N], nxt[M], to[M], dis[M], id;
int fa[N][19];
int dep[N];
ll delta[N];
int SV;
void add(int u, int v, int w);
void Dijkstra(int S);
void build();
}  // namespace Graph

short tos(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a';
  } else {
    return 26 + c - 'A';
  }
}

char ch[N];
int pos[N];
int lg2[N];
int n, k;
ll A, B, C, D, E;

int main() {
  scanf("%s", ch + 1);
  n = strlen(ch + 1);
  for (int i = 1; i <= n; ++i) {
    P.extend(tos(ch[i]));
    pos[i] = P.las;
  }
  lg2[1] = 0;
  for (int i = 2; i <= n; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  read(k), read(A), read(B), read(C), read(D), read(E);
  using namespace Graph;
  build();
  bool flag = true;
  for (int i = 1; i <= n; ++i) {
    flag &= (ch[i] == ch[n - i + 1]);
  }
  int q;
  read(q);
  while (q--) {
    int l, r;
    read(l), read(r);
    if (l == 1 && r == n) {
      write(0), EL;
      continue;
    }
    int now = pos[r];
    if (P.tre[now].len > r - l + 1) {
      for (int i = lg2[n]; i >= 0; --i) {
        if (fa[now][i] && P.tre[fa[now][i]].len > r - l + 1) {
          now = fa[now][i];
        }
      }
      now = fa[now][0];
    }
    write(delta[now] + (r - l + 1 - P.tre[now].len) * 1ll * E + (!flag) * A), EL;
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

int PAM::getfail(int las) {
  while (S[len] != S[len - tre[las].len - 1]) {
    las = tre[las].lnk;
  }
  return las;
}
void PAM::extend(short c) {
  S[++len] = c;
  int now = getfail(las);
  if (!tre[now].to[c]) {
    ++tot;
    tre[tot].len = tre[now].len + 2;
    tre[tot].lnk = tre[getfail(tre[now].lnk)].to[c];
    tre[now].to[c] = tot;
  }
  las = tre[now].to[c];
  tre[las].par = now;
}
void Graph::add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
void Graph::Dijkstra(int S) {
  for (int i = 1; i <= SV; ++i) {
    delta[i] = iinf * 1ll * N;
  }
  delta[S] = 0;
  typedef std::pair<ll, int> pli;
  std::priority_queue<pli> pq;
  pq.push(pii(0, S));
  while (!pq.empty()) {
    ll d;
    int u;
    std::tie(d, u) = pq.top();
    pq.pop();
    d *= -1;
    if (d != delta[u]) {
      continue;
    }
    for (int i = hed[u]; i; i = nxt[i]) {
      int v = to[i];
      if (d + dis[i] < delta[v]) {
        delta[v] = d + dis[i];
        pq.push(pli(-delta[v], v));
      }
    }
  }
}
void Graph::build() {
  for (int i = 2; i <= P.tot; ++i) {
    if (P.tre[i].lnk > 1) {
      add(i, P.tre[i].lnk, A);
      add(P.tre[i].lnk, i, B);
    } else {
      add(i, 1, A);
      add(1, i, B);
    }
    for (int now = P.tre[i].par, j = 1; j <= k && now > 1; now = P.tre[now].par, ++j) {
      add(i, now, C);
    }
    int tmp = i + P.tot;
    add(tmp, i, 0);
    add(i, tmp, D);
    for (int j = 0; j < 52; ++j) {
      if (P.tre[i].to[j]) {
        add(tmp, P.tre[i].to[j] + P.tot, 0);
      }
    }
  }
  SV = P.tot << 1;
  Dijkstra(P.las);
  for (int i = 1; i <= P.tot; ++i) {
    fa[i][0] = P.tre[i].lnk;
    dep[i] = dep[fa[i][0]] + 1;
    for (int j = 1; j <= lg2[dep[i]]; ++j) {
      fa[i][j] = fa[fa[i][j - 1]][j - 1];
    }
  }
  for (int i = 2; i <= P.tot; ++i) {
    if (P.tre[i].lnk > 1) {
      delta[i] = min(delta[i], delta[P.tre[i].lnk] + (P.tre[i].len - P.tre[P.tre[i].lnk].len) * E);
    }
  }
}
