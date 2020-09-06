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
#include <ctime>
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

const int N = 50005;
const int M = 100005;
const int Lm = 1000000000;
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

class Info {
public:
  int minn, maxn, ansl, ansr;
  Info(int mi = 0, int mx = 0, int al = 0, int ar = 0) : minn(mi), maxn(mx), ansl(al), ansr(ar) {}
};

void add(int u, int v);
void dfs1(int u);
void dfs2(int u);
Info merge(Info i, Info j);
void Seg_build(int x, int xl, int xr);
void Seg_update(int x, int xl, int xr, int ul, int ur, int num);
Info Seg_query(int x, int xl, int xr, int ql, int qr);
void update(int u, int v, int num);
int query(int u, int v);

int hed[N], nxt[M], to[M], id;
int fa[N], dep[N], son[N], siz[N], top[N], ttl[N], ltt[N], id2;
int val[N];
Info seg[N << 2];
int tag[N << 2];
int n, q;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(val[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  dfs1(1);
  dfs2(1);
  Seg_build(1, 1, n);
  read(q);
  for (int i = 1; i <= q; ++i) {
    int u, v, num;
    read(u), read(v), read(num);
    write(query(u, v)), EL;
    update(u, v, num);
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
  ttl[u] = ++id2;
  ltt[id2] = u;
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
Info merge(Info i, Info j) {
  return Info(
    min(i.minn, j.minn),
    max(i.maxn, j.maxn),
    max(max(i.ansl, j.ansl), j.maxn - i.minn),
    max(max(i.ansr, j.ansr), i.maxn - j.minn)
  );
}
void Seg_down(int x) {
  if (tag[x]) {
    seg[lc(x)].minn += tag[x];
    seg[rc(x)].minn += tag[x];
    seg[lc(x)].maxn += tag[x];
    seg[rc(x)].maxn += tag[x];
    tag[lc(x)] += tag[x];
    tag[rc(x)] += tag[x];
    tag[x] = 0;
  }
}
void Seg_build(int x, int xl, int xr) {
  if (xl == xr) {
    seg[x] = Info(val[ltt[xl]], val[ltt[xr]]);
    return;
  }
  int xm = (xl + xr) >> 1;
  Seg_build(lc(x), xl, xm);
  Seg_build(rc(x), xm + 1, xr);
  seg[x] = merge(seg[lc(x)], seg[rc(x)]);
}
void Seg_update(int x, int xl, int xr, int ul, int ur, int num) {
  if (ul <= xl && xr <= ur) {
    tag[x] += num;
    seg[x].minn += num;
    seg[x].maxn += num;
    return;
  }
  Seg_down(x);
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    Seg_update(lc(x), xl, xm, ul, ur, num);
  }
  if (ur > xm) {
    Seg_update(rc(x), xm + 1, xr, ul, ur, num);
  }
  seg[x] = merge(seg[lc(x)], seg[rc(x)]);
}
Info Seg_query(int x, int xl, int xr, int ql, int qr) {
  if (ql <= xl && xr <= qr) {
    return seg[x];
  }
  Seg_down(x);
  int xm = (xl + xr) >> 1;
  Info ans(Lm);
  if (ql <= xm) {
    ans = merge(ans, Seg_query(lc(x), xl, xm, ql, qr));
  }
  if (qr > xm) {
    ans = merge(ans, Seg_query(rc(x), xm + 1, xr, ql, qr));
  }
  return ans;
}
void update(int u, int v, int num) {
  while (top[u] != top[v]) {
    if (dep[top[u]] > dep[top[v]]) {
      Seg_update(1, 1, n, ttl[top[u]], ttl[u], num);
      u = fa[top[u]];
    } else {
      Seg_update(1, 1, n, ttl[top[v]], ttl[v], num);
      v = fa[top[v]];
    }
  }
  if (dep[u] < dep[v]) {
    Seg_update(1, 1, n, ttl[u], ttl[v], num);
  } else {
    Seg_update(1, 1, n, ttl[v], ttl[u], num);
  }
}
int query(int u, int v) {
  Info l(Lm), r(Lm);
  while (top[u] != top[v]) {
    if (dep[top[u]] > dep[top[v]]) {
      Info tmp = Seg_query(1, 1, n, ttl[top[u]], ttl[u]);
      std::swap(tmp.ansl, tmp.ansr);
      l = merge(l, tmp);
      u = fa[top[u]];
    } else {
      Info tmp = Seg_query(1, 1, n, ttl[top[v]], ttl[v]);
      r = merge(tmp, r);
      v = fa[top[v]];
    }
  }
  if (dep[u] > dep[v]) {
    Info tmp = Seg_query(1, 1, n, ttl[v], ttl[u]);
    std::swap(tmp.ansl, tmp.ansr);
    l = merge(l, tmp);
  } else {
    Info tmp = Seg_query(1, 1, n, ttl[u], ttl[v]);
    r = merge(tmp, r);
  }
  return merge(l, r).ansl;
}

