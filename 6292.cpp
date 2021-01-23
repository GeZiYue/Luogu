#include <bits/stdc++.h>

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

constexpr int N = 200005;

namespace Fenwick {
ll num[N], sum[N];
void add(int x, int k);
ll query(int x);
void add(int l, int r, int k);
ll query(int l, int r);
}  // namespace Fenwick

namespace SAM {
class Node {
 public:
  int len, lnk;
  int to[26];
} tre[N];
int las = 1, tot = 1;
int extend(int c);
}  // namespace SAM

namespace LCT {
class Node {
 public:
  int ch[2], fa;
  int las, tag;
} tre[N];
#define lc(x) (tre[x].ch[0])
#define rc(x) (tre[x].ch[1])
#define fa(x) (tre[x].fa)
#define las(x) (tre[x].las)
#define tag(x) (tre[x].tag)
void access(int x, int now);
void init();
}  // namespace LCT

char ch[N];
int pos[N];
std::vector<pii> Q[N];
ll ans[N];
int n;

int main() {
  scanf("%s", ch + 1);
  n = strlen(ch + 1);
  for (int i = 1; i <= n; ++i) {
    pos[i] = SAM::extend(ch[i] - 'a');
  }
  int q;
  read(q);
  for (int i = 1; i <= q; ++i) {
    int l, r;
    read(l), read(r);
    Q[r].emplace_back(l, i);
  }
  LCT::init();
  for (int i = 1; i <= n; ++i) {
    LCT::access(pos[i], i);
    for (auto j : Q[i]) {
      ans[j.second] = Fenwick::query(j.first, i);
    }
  }
  for (int i = 1; i <= q; ++i) {
    write(ans[i]), EL;
  }
  return 0;
}

namespace Fenwick {
void add(int x, int k) {
  ll w = k * x;
  while (x <= n) {
    num[x] += k;
    sum[x] += w;
    x += x & -x;
  }
}
ll query(int x) {
  ll sn = 0, sm = 0;
  int i = x;
  while (i) {
    sn += num[i];
    sm += sum[i];
    i -= i & -i;
  }
  return sn * (x + 1) - sm;
}
void add(int l, int r, int k) { add(l, k), add(r + 1, -k); }
ll query(int l, int r) { return query(r) - query(l - 1); }
}  // namespace Fenwick

namespace SAM {
int extend(int c) {
  int now = ++tot;
  tre[now].len = tre[las].len + 1;
  int p = las;
  while (p && !tre[p].to[c]) {
    tre[p].to[c] = now;
    p = tre[p].lnk;
  }
  if (!p) {
    tre[now].lnk = 1;
  } else {
    int q = tre[p].to[c];
    if (tre[p].len + 1 == tre[q].len) {
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
  return las = now;
}
}  // namespace SAM

namespace LCT {
bool nroot(int x) { return lc(fa(x)) == x || rc(fa(x)) == x; }
bool getid(int x) { return rc(fa(x)) == x; }
void pushdown(int x) {
  if (tag(x)) {
    if (lc(x)) {
      las(lc(x)) = tag(lc(x)) = tag(x);
    }
    if (rc(x)) {
      las(rc(x)) = tag(rc(x)) = tag(x);
    }
    tag(x) = 0;
  }
}
void rotate(int x) {
  int y = fa(x), z = fa(y), yid = getid(x), zid = getid(y), w = tre[x].ch[yid ^ 1];
  tre[x].ch[yid ^ 1] = y;
  tre[y].ch[yid] = w;
  if (nroot(y)) {
    tre[z].ch[zid] = x;
  }
  fa(y) = x;
  if (w) {
    fa(w) = y;
  }
  fa(x) = z;
}
void pushdall(int x) {
  if (nroot(x)) {
    pushdall(fa(x));
  }
  pushdown(x);
}
void splay(int x) {
  pushdall(x);
  while (nroot(x)) {
    int y = fa(x);
    if (nroot(y)) {
      rotate(getid(x) == getid(y) ? y : x);
    }
    rotate(x);
  }
}
void access(int x, int now) {
  int tmp = x;
  for (int y = 0; x; x = fa(y = x)) {
    splay(x);
    tre[x].ch[1] = y;
    if (las(x)) {
      Fenwick::add(las(x) - SAM::tre[x].len + 1, las(x) - SAM::tre[fa(x)].len, -1);
    }
  }
  x = tmp;
  splay(x);
  las(x) = tag(x) = now;
  Fenwick::add(now - SAM::tre[x].len + 1, now, 1);
}
void init() {
  for (int i = 1; i <= SAM::tot; ++i) {
    fa(i) = SAM::tre[i].lnk;
  }
}
}  // namespace LCT

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
