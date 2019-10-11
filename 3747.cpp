#include <unordered_set>
#include <unordered_map>
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
const int M = 10005;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

class Res {
public:
  int res;
  bool flag;
  Res(int res = 0, bool flag = false) : res(res), flag(flag) {}
};

void build();
int getphi(int);
int query(int, int);
void update(int, int);

int a[N];
int num[N];
Res powa[M][100], powb[M][100];
int BIT[N];
int minn[N << 2], tag[N << 2];
int phi[N];
int h[N];
int n, m, p, c;
int lim;

int main () {
  read(n), read(m), read(p), read(c);
  phi[0] = p;
  for (int i = 1; ; ++i) {
    phi[i] = getphi(phi[i - 1]);
    if (phi[i] == 1) {
      phi[i + 1] = 1;
      lim = i + 1;
      break;
    }
  }
  for (int i = 0; i <= lim; ++i) {
    powa[0][i] = (phi[i] == 1 ? Res(0, true) : Res(1, false));
    for (int j = 1; j <= 10000; ++j) {
      ll tmp = powa[j - 1][i].res * 1ll * c;
      powa[j][i] = Res(tmp % phi[i], powa[j - 1][i].flag || (tmp >= phi[i]));
    }
  }
  for (int i = 0; i <= lim; ++i) {
    powb[0][i] = (phi[i] == 1 ? Res(0, true) : Res(1, false));
    powb[1][i] = powa[10000][i];
    for (int j = 2; j <= 10000; ++j) {
      ll tmp = powb[j - 1][i].res * 1ll * powa[10000][i].res;
      powb[j][i] = Res(tmp % phi[i], powb[j - 1][i].flag || (tmp >= phi[i]));
    }
  }
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  build();
  for (int i = 1; i <= m; ++i) {
    int ty, l, r;
    read(ty), read(l), read(r);
    if (ty) {
      write(query(l, r)), EL;
    } else {
      update(l, r);
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

int getphi(int x) {
  int ans = x;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      ans = ans / i * (i - 1);
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  if (x ^ 1) {
    ans = ans / x * (x - 1);
  }
  return ans;
}
inline Res power(int x, int p) {
  ll tmp = powa[x % 10000][p].res * 1ll * powb[x / 10000][p].res;
  return Res(tmp % phi[p], powa[x % 10000][p].flag || powb[x / 10000][p].flag || tmp >= phi[p]);
}
Res work(int x, int dep, int l) {
  int p = phi[dep];
  int now = (dep == l ? x : c);
  if (p == 1) {
    return Res(0, now);
  }
  if (dep == l) {
    return Res(now % p, now >= p);
  }
  Res res = work(x, dep + 1, l);
  if (res.flag) {
    res.res += phi[dep + 1];
  }
  return power(res.res, dep);
}
inline void pushup(int x) {
  minn[x] = min(minn[ls(x)], minn[rs(x)]);
}
inline void pushdown(int x) {
  if (tag[x]) {
    tag[ls(x)] += tag[x];
    tag[rs(x)] += tag[x];
    minn[ls(x)] += tag[x];
    minn[rs(x)] += tag[x];
    tag[x] = 0;
  }
}
int query(int x, int xl, int xr, int ql, int qr) {
  if (xl >= ql && xr <= qr) {
    return minn[x];
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  int res = iinf;
  if (xm >= ql) {
    res = min(query(ls(x), xl, xm, ql, qr), res);
  }
  if (xm < qr) {
    res = min(query(rs(x), xm + 1, xr, ql, qr), res);
  }
  return res;
}
void update(int x, int xl, int xr, int ul, int ur) {
  if (xl >= ul && xr <= ur) {
    ++minn[x], ++tag[x];
    return;
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  if (xm >= ul) {
    update(ls(x), xl, xm, ul, ur);
  }
  if (xm < ur) {
    update(rs(x), xm + 1, xr, ul, ur);
  }
  pushup(x);
}
inline int BITquery(int x) {
  int ans = 0;
  while (x) {
    ans = (ans + BIT[x] + p) % p;
    x -= (x & (-x));
  }
  return ans;
}
inline void BITupdate(int x, int num) {
  while (x <= n) {
    BIT[x] = (BIT[x] + num + p) % p;
    x += (x & (-x));
  }
}
inline void build() {
  for (int i = 1; i <= n; ++i) {
    BITupdate(i, a[i]);
    num[i] = a[i];
  }
}
inline int query(int l, int r) {
  return (BITquery(r) + p - BITquery(l - 1)) % p;
}
inline void update(int l, int r) {
  if (query(1, 1, n, l, r) > lim) {
    return;
  }
  update(1, 1, n, l, r);
  for (int i = l; i <= r; ++i) {
    if (h[i] > lim) {
      continue;
    }
    ++h[i];
    int now = work(a[i], 0, h[i]).res;
    BITupdate(i, now - num[i]);
    num[i] = now;
  }
}
