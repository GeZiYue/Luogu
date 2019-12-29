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
const int N = 101005;
const int M = 100005;

class Node {
public:
  int fa, ch[2];
  int val, maxn;
  bool rev;
};
Node tre[N];
#define fa(x) (tre[x].fa)
#define lc(x) (tre[x].ch[0])
#define rc(x) (tre[x].ch[1])
#define val(x) (tre[x].val)
#define maxn(x) (tre[x].maxn)
#define rev(x) (tre[x].rev)
int sta[N];
void splay(int);
void access(int);
int findroot(int);
void makeroot(int);
void split(int, int);
void link(int, int);
void cut(int, int);

class Edge {
public:
  int u, v, w;
  bool operator < (const Edge &i) const {
    return w < i.w;
  }
};
Edge e[M];

int find(int);

bool exi[M];
int fa[N];
int n, m, q;
int op[M], a[M], b[M];
std::map<pii, int> mp;
int ans[M], cnt;

int main () {
  read(n), read(m), read(q);
  for (int i = 1; i <= m; ++i) {
    read(e[i].u), read(e[i].v), read(e[i].w);
    if (e[i].u > e[i].v) {
      std::swap(e[i].u, e[i].v);
    }
  }
  sort(e + 1, e + m + 1);
  for (int i = 1; i <= m; ++i) {
    exi[i] = true;
    mp[pii(e[i].u, e[i].v)] = i;
  }
  for (int i = 1; i <= q; ++i) {
    read(op[i]), read(a[i]), read(b[i]);
    if (a[i] > b[i]) {
      std::swap(a[i], b[i]);
    }
    if (op[i] == 2) {
      a[i] = mp[pii(a[i], b[i])];
      exi[a[i]] = false;
    }
  }
  for (int i = 1; i <= m; ++i) {
    val(i + n) = i;
  }
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
  for (int i = 1; i <= m; ++i) {
    if (exi[i]) {
      int fu = find(e[i].u), fv = find(e[i].v);
      if (fu ^ fv) {
        fa[fu] = fv;
        link(e[i].u, i + n);
        link(e[i].v, i + n);
      }
    }
  }
  for (int i = q; i >= 1; --i) {
    if (op[i] == 1) {
      split(a[i], b[i]);
      ans[++cnt] = e[maxn(b[i])].w;
    } else {
      int u = e[a[i]].u, v = e[a[i]].v;
      split(u, v);
      int now = maxn(v);
      if (now > a[i]) {
        int ul = e[now].u, vl = e[now].v;
        cut(ul, now + n);
        cut(vl, now + n);
        link(u, a[i] + n);
        link(v, a[i] + n);
      }
    }
  }
  for (int i = cnt; i >= 1; --i) {
    write(ans[i]), EL;
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

inline void reverse(int x) {
  lc(x) ^= rc(x) ^= lc(x) ^= rc(x);
  rev(x) ^= 1;
}
inline void pushup(int x) {
  maxn(x) = max(max(maxn(lc(x)), maxn(rc(x))), val(x));
}
inline void pushdown(int x) {
  if (rev(x)) {
    reverse(lc(x));
    reverse(rc(x));
    rev(x) = false;
  }
}
inline bool nroot(int x) {
  return lc(fa(x)) == x || rc(fa(x)) == x;
}
inline bool getid(int x) {
  return rc(fa(x)) == x;
}
inline void rotate(int x) {
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
inline void splay(int x) {
  int y = x, z = 0;
  sta[++z] = y;
  while (nroot(y)) {
    sta[++z] = y = fa(y);
  }
  while (z) {
    pushdown(sta[z--]);
  }
  while (nroot(x)) {
    y = fa(x);
    if (nroot(y)) {
      rotate(getid(x) == getid(y) ? y : x);
    }
    rotate(x);
  }
  pushup(x);
}
inline void access(int x) {
  for (int y = 0; x; x = fa(y = x)) {
    splay(x), rc(x) = y, pushup(x);
  }
}
inline int findroot(int x) {
  access(x), splay(x);
  while (true) {
    pushdown(x);
    if (lc(x)) {
      x = lc(x);
    } else {
      splay(x);
      return x;
    }
  }
}
inline void makeroot(int x) {
  access(x), splay(x), reverse(x);
}
inline void split(int x, int y) {
  makeroot(x), access(y), splay(y);
}
inline void link(int x, int y) {
  split(x, y);
  fa(x) = y;
}
inline void cut(int x, int y) {
  split(x, y);
  fa(x) = lc(y) = 0;
  pushup(y);
}
int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}
