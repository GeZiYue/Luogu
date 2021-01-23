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
#include <numeric>
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

constexpr int N = 400005;
constexpr int M = 800005;

namespace LCT {
class Node {
 public:
  int ch[2], fa;
  ll sum, val, vrs;
};
Node tre[N];
#define lc(x) (tre[x].ch[0])
#define rc(x) (tre[x].ch[1])
#define fa(x) (tre[x].fa)
#define sum(x) (tre[x].sum)
#define val(x) (tre[x].val)
#define vrs(x) (tre[x].vrs)
bool nroot(int x);
bool getid(int x);
void pushup(int x);
void rotate(int x);
void splay(int x);
ll calc(int x, ll t, ll h);
void access(int x, int w);
void dfs(int u);
}  // namespace LCT

void add(int u, int v);

int hed[N], nxt[M], to[M], id;
ll ans;
int n, q;

int main() {
  using namespace LCT;
  read(n), read(q);
  for (int i = 1; i <= n; ++i) {
    read(val(i));
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  dfs(1);
  write(ans), EL;
  for (int i = 1; i <= q; ++i) {
    int x, w;
    read(x), read(w);
    access(x, w);
    write(ans), EL;
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

bool LCT::nroot(int x) { return lc(fa(x)) == x || rc(fa(x)) == x; }
bool LCT::getid(int x) { return rc(fa(x)) == x; }
void LCT::pushup(int x) { sum(x) = sum(lc(x)) + sum(rc(x)) + val(x) + vrs(x); }
void LCT::rotate(int x) {
  int y = fa(x), z = fa(y), yid = getid(x), zid = getid(y), w = tre[x].ch[yid ^ 1];
  if (nroot(y)) {
    tre[z].ch[zid] = x;
  }
  tre[x].ch[yid ^ 1] = y;
  tre[y].ch[yid] = w;
  if (w) {
    fa(w) = y;
  }
  fa(x) = z;
  fa(y) = x;
  pushup(y);
}
void LCT::splay(int x) {
  int y;
  while (nroot(x)) {
    y = fa(x);
    if (nroot(y)) {
      rotate((getid(x) == getid(y)) ? y : x);
    }
    rotate(x);
  }
  pushup(x);
}
ll LCT::calc(int x, ll t, ll h) {
  if (rc(x)) {
    return (t - h) * 2;
  } else {
    if (val(x) * 2 > t) {
      return (t - val(x)) * 2;
    } else {
      return t - 1;
    }
  }
}
void LCT::access(int x, int w) {
  splay(x);
  ll t = sum(x) - sum(lc(x)), h = sum(rc(x));
  ans -= calc(x, t, h);
  t += w, sum(x) += w, val(x) += w;
  if (h * 2 <= t) {
    vrs(x) += h;
    rc(x) = 0;
    h = 0;
  }
  ans += calc(x, t, h);
  pushup(x);
  int y;
  for (x = fa(y = x); x; x = fa(y = x)) {
    splay(x);
    ll t = sum(x) - sum(lc(x)), h = sum(rc(x));
    ans -= calc(x, t, h);
    t += w, sum(x) += w, vrs(x) += w;
    if (h * 2 <= t) {
      vrs(x) += h;
      rc(x) = 0;
      h = 0;
    }
    if (sum(y) * 2 > t) {
      vrs(x) -= sum(y);
      rc(x) = y;
      h = sum(y);
    }
    ans += calc(x, t, h);
    pushup(x);
  }
}
void LCT::dfs(int u) {
  sum(u) = val(u);
  int pos = 0;
  ll mx = val(u);
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa(u)) {
      fa(v) = u;
      dfs(v);
      sum(u) += sum(v);
      if (sum(v) > mx) {
        mx = sum(pos = v);
      }
    }
  }
  ans += min(sum(u) - 1, (sum(u) - mx) * 2);
  if (mx * 2 > sum(u)) {
    rc(u) = pos;
  }
  vrs(u) = sum(u) - val(u) - sum(rc(u));
}
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
